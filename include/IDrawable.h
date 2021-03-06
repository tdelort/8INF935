#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>

class IDrawable {
public:
    IDrawable(GLuint program);
    void Init(GLfloat vertex[], size_t sizeVertex, GLfloat colors[], size_t sizeColors, GLuint ebo[], size_t sizeEbo);
    virtual void Draw() const = 0;
    virtual void SetPosition(const glm::vec3& position);
    virtual void SetRotation(const glm::vec3& rotation);
protected:

    GLuint m_vao;
    GLuint m_vertexVbo, m_colorsVbo, m_facesVbo;
    GLuint m_ebo;

    GLuint m_program;

    GLint m_modelUni, m_viewUni, m_projUni, m_albedoUni;
};