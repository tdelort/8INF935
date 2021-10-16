#pragma once

#include "IDrawable.h"

#include <glad/glad.h>

#include <glm/glm.hpp>

class Cube : public IDrawable
{
public:
    Cube(GLuint program);
    ~Cube();

    void Draw(glm::mat4 proj, glm::mat4 view) override;

private:
    glm::mat4 m_transform;

    GLuint m_vao;
    GLuint m_vertexVbo, m_colorsVbo, m_facesVbo;
    GLuint m_ebo;

    GLuint m_program;

    GLint m_modelUni, m_viewUni, m_projUni;
};