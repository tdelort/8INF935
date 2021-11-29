#include "Cube.h"
#include "Camera.h"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

Cube::Cube(GLuint program)
    : IDrawable(program), m_T(1.0f), m_R(1.0f), m_S(1.0f), m_albedo(1.0f)
{
    /** front  back
     *   3 2   7 6
     *   0 1   4 5
     */
    GLfloat cubeVertex[] = {
        -0.5f, -0.5f,  0.5f,
         0.5,  -0.5f,  0.5f,
         0.5,   0.5f,  0.5f,
        -0.5,   0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5,  -0.5f, -0.5f,
         0.5,   0.5f, -0.5f,
        -0.5,   0.5f, -0.5f,
    };

    GLfloat cubeColors[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f,

        0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
    };

    GLuint cubeFaces[] = {
        0, 1, 2,
        2, 3, 0,
        1, 5, 6,
        6, 2, 1,
        5, 4, 7,
        7, 6, 5,
        4, 0, 3, 
        3, 7, 4,
        2, 6, 7,
        7, 3, 2,
        4, 5, 1,
        1, 0, 4
    };

    Init(cubeVertex, sizeof(cubeVertex), cubeColors, sizeof(cubeColors), cubeFaces, sizeof(cubeFaces));

    m_modelUni = glGetUniformLocation(m_program, "model");
    m_viewUni = glGetUniformLocation(m_program, "view");
    m_projUni = glGetUniformLocation(m_program, "proj");
    m_albedoUni = glGetUniformLocation(m_program, "albedo");
}

Cube::~Cube()
{
    //TODO
}

void Cube::Draw() const
{
    glUseProgram(m_program);
    glBindVertexArray(m_vao);
    glm::mat4 trans = m_T * m_R * m_S;
    glUniformMatrix4fv(m_modelUni, 1, GL_FALSE, glm::value_ptr(trans));
    glUniformMatrix4fv(m_projUni, 1, GL_FALSE, glm::value_ptr(Camera::getProj()));
    glUniformMatrix4fv(m_viewUni, 1, GL_FALSE, glm::value_ptr(Camera::getView()));
    glUniform3fv(m_albedoUni, 1, glm::value_ptr(m_albedo));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void Cube::SetPosition(const glm::vec3& position)
{
    m_T = glm::translate(glm::mat4(1.0f), position);
}

void Cube::SetRotation(const glm::vec3& rotation)
{
    glm::mat4 rX = glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 rY = glm::rotate(glm::mat4(1.0f), rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rZ = glm::rotate(glm::mat4(1.0f), rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    m_R = rZ * rY * rX;
}

void Cube::SetScale(const glm::vec3& scale)
{
    m_S = glm::scale(glm::mat4(1.0f), scale);
}

void Cube::SetColor(const glm::vec3& rgb)
{
    m_albedo = rgb;
}