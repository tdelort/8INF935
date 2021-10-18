#pragma once

#include "IDrawable.h"

#include <glad/glad.h>

#include <glm/glm.hpp>

class Cube : public IDrawable
{
public:
    Cube(GLuint program);
    ~Cube();

    void Draw(glm::mat4 proj, glm::mat4 view) const override;

    void SetPosition(const glm::vec3& position);
    void SetRotation(const glm::vec3& rotation);
    void SetScale(const glm::vec3& scale);
    void SetColor(const glm::vec3& rgb);

private:
    glm::vec3 m_albedo;
    glm::mat4 m_T;
    glm::mat4 m_R;
    glm::mat4 m_S;

    GLuint m_vao;
    GLuint m_vertexVbo, m_colorsVbo, m_facesVbo;
    GLuint m_ebo;

    GLuint m_program;

    GLint m_modelUni, m_viewUni, m_projUni, m_albedoUni;
};