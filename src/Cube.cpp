#include "Cube.h"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

Cube::Cube(GLuint program)
    : m_program(program), m_T(1.0f), m_R(1.0f), m_S(1.0f), m_albedo(1.0f)
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

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    // Vertex Data
    glGenBuffers(1, &m_vertexVbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertex), cubeVertex, GL_STATIC_DRAW);

    GLint positionAttrib = glGetAttribLocation(program, "position");
    glVertexAttribPointer(positionAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(positionAttrib);

    // Colors Data
    glGenBuffers(1, &m_colorsVbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorsVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeColors), cubeColors, GL_STATIC_DRAW);

    GLint colorAttrib = glGetAttribLocation(program, "color");
    glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(colorAttrib);

    // EBO
    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeFaces), cubeFaces, GL_STATIC_DRAW);

    m_modelUni = glGetUniformLocation(program, "model");
    m_viewUni = glGetUniformLocation(program, "view");
    m_projUni = glGetUniformLocation(program, "proj");
    m_albedoUni = glGetUniformLocation(program, "albedo");
}

Cube::~Cube()
{

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