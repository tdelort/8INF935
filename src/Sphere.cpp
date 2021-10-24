#include "Sphere.h"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

Cube::Cube(GLuint program)
    : IDrawable(program), m_T(1.0f), m_R(1.0f), m_S(1.0f), m_albedo(1.0f)
{   
    //init points here
    GLfloat sphereVertex[] {
        //fill
    };
    GLfloat sphereColors[] {
        //fill
    };
    GLuint sphereFaces[] {
        //fill
    };

    Init(sphereVertex, sizeof(sphereVertex), sphereColors, sizeof(sphereColors), sphereFaces, sizeof(sphereFaces));

    m_modelUni = glGetUniformLocation(m_program, "model");
    m_viewUni = glGetUniformLocation(m_program, "view");
    m_projUni = glGetUniformLocation(m_program, "proj");
    m_albedoUni = glGetUniformLocation(m_program, "albedo");
}

Cube::~Cube()
{
    //TODO
}

void Cube::Draw(glm::mat4 proj, glm::mat4 view) const
{
    glUseProgram(m_program);
    glBindVertexArray(m_vao);
    glm::mat4 trans = m_T * m_S * m_R;
    glUniformMatrix4fv(m_modelUni, 1, GL_FALSE, glm::value_ptr(trans));
    glUniformMatrix4fv(m_projUni, 1, GL_FALSE, glm::value_ptr(proj));
    glUniformMatrix4fv(m_viewUni, 1, GL_FALSE, glm::value_ptr(view));
    glUniform3fv(m_albedoUni, 1, glm::value_ptr(m_albedo));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void Cube::SetPosition(const glm::vec3& position)
{
    m_T = glm::translate(glm::mat4(1.0f), position);
}

void Cube::SetRotation(const glm::vec3& position)
{
    glm::mat4 rX = glm::rotate(glm::mat4(1.0f), position.x, glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 rY = glm::rotate(glm::mat4(1.0f), position.y, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rZ = glm::rotate(glm::mat4(1.0f), position.z, glm::vec3(0.0f, 0.0f, 1.0f));
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