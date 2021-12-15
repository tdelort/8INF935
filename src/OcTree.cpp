#include "OcTree.h"

#include "colliders/Primitive.h"

#ifdef OCTREE_DEBUG
#include "Cube.h"
#include "Shader.h"
#include <glm/glm.hpp>
#endif

#define OT_NEW_CENTER(c, h, i) (c + ((h * 0.5) * Vector3D(i & 0b1 ? 1 : -1, i & 0b10 ? 1 : -1, i & 0b100 ? 1 : -1)))

OcTree::OcTree() : OcTree(Vector3D(0, 0, 0), Vector3D(10, 10, 10)) {}

OcTree::OcTree(Vector3D center, Vector3D halfSize)
    : m_center(center), m_halfSize(halfSize)
{
    Node root;
    root.locCode = 0b1;
    root.subdivided = false;
#ifdef OCTREE_DEBUG
    root.debugCube = new Cube(createProgram(true));
    root.debugCenter = glm::vec3(center.x(), center.y(), center.z());
    root.debugHalfSize = glm::vec3(halfSize.x(), halfSize.y(), halfSize.z());
#endif
    m_nodes.insert(std::pair<uint32_t, Node>(0b1, root));
    std::cout << "OcTree created with center: " << center << " and halfSize: " << halfSize << std::endl;
}

int OcTree::_GetIndex(AABB aabb, Vector3D center, Vector3D halfSize) const
{
    Vector3D himin = aabb.min > center;
    Vector3D himax = aabb.max < (center + halfSize);
    Vector3D lomin = aabb.min > (center - halfSize);
    Vector3D lomax = aabb.max < center;
    Vector3D lo = lomin && lomax;
    Vector3D hi = himin && himax;
    
    if(lo + hi != Vector3D(1, 1, 1))
        return -1;

    return (int)hi.x() ^ 0b10 * (int)hi.y() ^ 0b100 * (int)hi.z();
}

void OcTree::_Insert(Primitive* obj, AABB aabb, uint8_t depth, uint32_t locCodeAcc, Vector3D center, Vector3D halfSize)
{
    //std::cout << "_Inserting at depth " << (int)depth << std::endl;
    // TODO : check if node != m_nodes.end()
    auto node_it = m_nodes.find(locCodeAcc);
    assert(node_it != m_nodes.end()); // should never happen

    // If this is true, this means we subdivided the node and we need to insert the object in its children
    if (node_it->second.subdivided)
    {
        //std::cout << "Node already subdivided" << std::endl;
        // Check in which child the object should be inserted
        int index = _GetIndex(aabb, center, halfSize);
        if (index != -1)
        {
            // If it can be inserted in one of the children, do it
            Vector3D newCenter = OT_NEW_CENTER(center, halfSize, index);
            _Insert(obj, aabb, depth + 1, (locCodeAcc << 3) | index, newCenter, halfSize * 0.5);
            return;
        }
    }

    // If we are here, either the node was not subdivided or the object can't be inserted in any of the children
    // In both cases, we insert the object in the node
    node_it->second.objects.push_back(obj);
    //std::cout << "Number of objects in node : " << node_it->second.objects.size() << std::endl;
    if (node_it->second.objects.size() > MAX_OBJECTS_PER_NODE && depth < MAX_DEPTH)
    {
        //std::cout << "Subdividing node" << std::endl;
        // If we are here, the node contains too many objects and we need to subdivide it
        if (node_it->second.subdivided)
            return;
        
        // Subdivide the node
        for(int i = 0; i < 8; i++)
        {
            Node child;
            child.locCode = (locCodeAcc << 3) | i; // loccode with 0b000 to 0b111 after it
            child.subdivided = false;
#ifdef OCTREE_DEBUG
            child.debugCube = new Cube(createProgram(true));
            Vector3D nc = OT_NEW_CENTER(center, halfSize, i);
            child.debugCenter = glm::vec3(nc.x(), nc.y(), nc.z());
            Vector3D hs = halfSize * 0.5;
            child.debugHalfSize = glm::vec3(hs.x(), hs.y(), hs.z());
#endif
            m_nodes.insert(std::make_pair(child.locCode, child));
        }
        node_it->second.subdivided = true;

        // For each nodes, we try to put them in the children
        auto it = node_it->second.objects.begin();
        while(it != node_it->second.objects.end())
        {
            // Compute the index of the child where the object should be inserted
            int index = _GetIndex((*it)->GetAABB(), center, halfSize);
            if (index != -1)
            {
                // If it can be inserted in one of the children, do it
                Vector3D newCenter = OT_NEW_CENTER(center, halfSize, index);
                _Insert(*it, (*it)->GetAABB(), depth + 1, (locCodeAcc << 3) | index, newCenter, halfSize * 0.5);
                it = node_it->second.objects.erase(it);
            }
            else
            {
                // If it can't be inserted in any of the children, we move to the next object
                it++;
            }
        }
    }
}

bool OcTree::Insert(Primitive* obj)
{
    AABB aabb = obj->GetAABB();

    // Check if the object fits inside the root
    Vector3D min = aabb.min > m_center + m_halfSize; // 1 on any dimension means the object is outside the root
    Vector3D max = aabb.max < m_center - m_halfSize;
    if(min != Vector3D(0, 0, 0) || max != Vector3D(0, 0, 0))
        return false;

    _Insert(obj, aabb, 0, 0b1, m_center, m_halfSize);
    return true;
}


std::vector<Primitive*> OcTree::_Query(AABB aabb, int depth, uint32_t locCodeAcc, Vector3D center, Vector3D halfSize) const
{
    if(depth > MAX_DEPTH)
        return std::vector<Primitive*>();

    auto node_it = m_nodes.find(locCodeAcc);
    assert(node_it != m_nodes.end()); // should never happen

    int index = _GetIndex(aabb, center, halfSize);

    std::vector<Primitive*> returnObjects;
    if(index != -1 && node_it->second.subdivided)
    {
        returnObjects = _Query(aabb, depth + 1, (locCodeAcc << 3) | index, OT_NEW_CENTER(center, halfSize, index), halfSize * 0.5);
    }
    returnObjects.insert(returnObjects.end(), node_it->second.objects.cbegin(), node_it->second.objects.cend());
    return returnObjects;
}

// returns all objects that could collide with obj (including obj)
std::vector<Primitive*> OcTree::Query(Primitive* obj) const
{
    return _Query(obj->GetAABB(), 0, 0b1, m_center, m_halfSize);
}

void OcTree::Clear()
{
    m_nodes.clear();
}

uint8_t OcTree::depth(uint32_t value)
{
    // TODO : can be changed with a plaftorm specific function
    int bit = 0;
    while (value >>= 3) bit++;
    return bit;
}

void OcTree::Draw() const
{
#ifdef OCTREE_DEBUG
    for(auto it = m_nodes.begin(); it != m_nodes.end(); it++)
    {
        Node node = it->second;
        node.debugCube->SetPosition(node.debugCenter);
        node.debugCube->SetScale(node.debugHalfSize * 2.0f);
        int depth = OcTree::depth(it->second.locCode);
        /*
        if(depth == 0)
            node.debugCube->SetColor(glm::vec3(1, 0, 0));
        else if (depth == 1)
        {
            node.debugCube->SetColor(glm::vec3(0, 1, 0));
        }
        else if (depth == 2)
        {
            node.debugCube->SetColor(glm::vec3(0, 0, 1));
        }
        else
        {
            node.debugCube->SetColor(glm::vec3(1, 1, 0));
        }
        */
        node.debugCube->SetColor(glm::vec3(0, 1, 1));

        node.debugCube->Draw();
    }
#endif
}