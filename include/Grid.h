#pragma once

#include "IDrawable.h"

#include <glad/glad.h>

#include <glm/glm.hpp>

class Grid : public IDrawable
{
public:
    Grid();
    ~Grid();

    void Draw(glm::mat4 proj, glm::mat4 view) const override;

    void SetSize(float size);

private:
    float m_size;

    GLuint m_vao;
    GLuint m_vertexVbo, m_colorsVbo, m_facesVbo;
    GLuint m_ebo;

    GLuint m_program;

    GLint m_sizeUni, m_viewUni, m_projUni;

    //"small" helper function
    GLuint CreateProgram() const;
};