#pragma once

#include "colliders/Primitive.h"

#include <stdint.h>
#include <unordered_map>

//#define OCTREE_DEBUG

#ifdef OCTREE_DEBUG
#include "Cube.h"
#include "Shader.h"
#include <glm/glm.hpp>
#endif


/**
 *  Location codes : 
 *  0bXYZ : 
 *  - if X is 1, the node is in the positive X direction
 *  - if Y is 1, the node is in the positive Y direction
 *  - if Z is 1, the node is in the positive Z direction
 *  
 *  0b1 X1 Y1 Z1 X2 Y2 Z2 . . .
 *  Each Xn Yn Zn is the node position at the level n
 *  The first 1 is to help differentiate between 000 XYZ and XYZ, it is also used to compute the depth of the node.
 */

class OcTree
{
public :
    static const uint32_t MAX_DEPTH = 3; //only the root is depth 0. So depth 3 means 3 subdivisions occured.
    static const uint32_t MAX_OBJECTS_PER_NODE = 4;
    // NB NODES = (8^(DEPTH+1) - 1) / 7 <=> ((1 << 3 * depth) - 1) / 7
    
    Vector3D m_center;
    Vector3D m_halfSize;

    struct Node
    {
#ifdef OCTREE_DEBUG
        Cube* debugCube;
        glm::vec3 debugCenter;
        glm::vec3 debugHalfSize;
#endif
        std::vector<Primitive*> objects;
        uint32_t locCode;
        bool subdivided;
    };

    std::unordered_map<uint32_t, Node> m_nodes;

    int _GetIndex(AABB aabb, Vector3D center, Vector3D halfSize) const;
    std::vector<Primitive*> _Query(AABB aabb, int depth, uint32_t locCodeAcc, Vector3D center, Vector3D halfSize) const;
    void _Insert(Primitive* obj, AABB aabb, uint8_t depth, uint32_t locCodeAcc, Vector3D center, Vector3D halfSize);
    static uint8_t depth(uint32_t value);

public:
    OcTree(Vector3D center, Vector3D halfSize);
    OcTree();

    // returns all objects that could collide with obj (including obj)
    std::vector<Primitive*> Query(Primitive* obj) const;
    bool Insert(Primitive* obj);
    void Clear();
    void Draw() const;
};
