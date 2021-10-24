#pragma once

#include "IDrawable.h"

#include <glad/glad.h>

#include <glm/glm.hpp>

class Grid : public IDrawable
{
public:
    Grid(GLuint program);
    ~Grid();

    void Draw(glm::mat4 proj, glm::mat4 view) const override;

    //"small" helper function
    static GLuint CreateProgram();
private:
    static const int size = 50;
    GLint m_sizeUni, m_viewUni, m_projUni;
};