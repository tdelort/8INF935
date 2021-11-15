#include "IDrawable.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

IDrawable::IDrawable(GLuint program)
    : m_program(program)
{}

void IDrawable::Init(GLfloat* vertex, size_t sizeVertex, GLfloat* colors, size_t sizeColors, GLuint* ebo, size_t sizeEbo)
{
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    // Vertex Data
    glGenBuffers(1, &m_vertexVbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeVertex, vertex, GL_STATIC_DRAW);

    GLint positionAttrib = glGetAttribLocation(m_program, "position");
    glVertexAttribPointer(positionAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(positionAttrib);

    // Colors Data
    glGenBuffers(1, &m_colorsVbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorsVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeColors, colors, GL_STATIC_DRAW);

    GLint colorAttrib = glGetAttribLocation(m_program, "color");
    glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(colorAttrib);

    // EBO
    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeEbo, ebo, GL_STATIC_DRAW);

}
