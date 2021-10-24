#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>

class IDrawable {
public:
    IDrawable(GLuint program);
    void Init(GLfloat vertex[], size_t sizeVertex, GLfloat colors[], size_t sizeColors, GLuint ebo[], size_t sizeEbo);
    virtual void Draw(glm::mat4 proj, glm::mat4 view) const = 0;
protected:

    GLuint m_vao;
    GLuint m_vertexVbo, m_colorsVbo, m_facesVbo;
    GLuint m_ebo;

    GLuint m_program;

    GLint m_modelUni, m_viewUni, m_projUni, m_albedoUni;
};