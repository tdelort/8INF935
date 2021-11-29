#include "ObjMesh.h"
#include "Camera.h"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

ObjMesh::ObjMesh(GLuint program, const std::string& fileName)
    : IDrawable(program), m_T(1.0f), m_R(1.0f), m_S(1.0f), m_albedo(1.0f)
{
    std::ifstream file;

    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);    

    try
    {   
        file.open(fileName);
    }
    catch (std::system_error& e)
    {
        std::cerr << "Exception : " << fileName << std::endl;
        std::cerr << e.code().message() << std::endl;
    }

    if(!file.is_open())
    {
        std::cerr << "Error opening file: " << fileName << std::endl;
        return;
    }

    std::vector<GLfloat> vertices;
    std::vector<GLfloat> vertexColors;
    std::vector<GLuint> faces;
    std::string line;
    int i = 0;
    try
    {
        while (std::getline(file, line))
        {
            i++;
            if(line.length() == 0)
            {
                //file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            if (line.substr(0, 2) == "v ")
            {
                std::istringstream s(line.substr(2));
                float x, y, z;
                s >> x;
                s >> y;
                s >> z;
                vertices.push_back(x);
                vertices.push_back(y);
                vertices.push_back(z);

                //For now, just use white color
                float r, g, b;
                //random color
                r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                vertexColors.push_back(r);
                vertexColors.push_back(g);
                vertexColors.push_back(b);
            }
            else if (line.substr(0, 2) == "f ")
            {
                std::istringstream s(line.substr(2));
                std::vector<unsigned int> face;
                unsigned int v;
                s >> v;
                faces.push_back(v - 1);
                s >> v;
                faces.push_back(v - 1);
                s >> v;
                faces.push_back(v - 1);
            }
            else
            {
                // Ignore other kind of data
                std::cout << "Ignoring line: " << line << std::endl;
            }

        }
    }
    catch (std::system_error& e)
    {
        //ignore exception
    }

    m_numIndices = faces.size();
    Init(vertices.data(), vertices.size() * sizeof(GLfloat), vertexColors.data(), vertexColors.size() * sizeof(GLfloat), faces.data(), faces.size() * sizeof(GLuint));

    m_modelUni = glGetUniformLocation(program, "model");
    m_viewUni = glGetUniformLocation(program, "view");
    m_projUni = glGetUniformLocation(program, "proj");
    m_albedoUni = glGetUniformLocation(program, "albedo");

    file.close();
}

ObjMesh::~ObjMesh()
{
    //TODO
}

void ObjMesh::Draw() const
{
    glUseProgram(m_program);
    glBindVertexArray(m_vao);
    glm::mat4 trans = m_T * m_S * m_R;
    glUniformMatrix4fv(m_modelUni, 1, GL_FALSE, glm::value_ptr(trans));
    glUniformMatrix4fv(m_projUni, 1, GL_FALSE, glm::value_ptr(Camera::getProj()));
    glUniformMatrix4fv(m_viewUni, 1, GL_FALSE, glm::value_ptr(Camera::getView()));
    glUniform3fv(m_albedoUni, 1, glm::value_ptr(m_albedo));
    glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0);
}

void ObjMesh::SetPosition(const glm::vec3& pos)
{
    m_T = glm::translate(glm::mat4(1.0f), pos);
}

void ObjMesh::SetRotation(const glm::vec3& rotation)
{
    glm::mat4 rX = glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 rY = glm::rotate(glm::mat4(1.0f), rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rZ = glm::rotate(glm::mat4(1.0f), rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    m_R = rZ * rY * rX;
}

void ObjMesh::SetScale(const glm::vec3& scale)
{
    m_S = glm::scale(glm::mat4(1.0f), scale);
}

void ObjMesh::SetColor(const glm::vec3& rgb)
{
    m_albedo = rgb;
}

