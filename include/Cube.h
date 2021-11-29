#pragma once

#include "IDrawable.h"

#include <glad/glad.h>

#include <glm/glm.hpp>

class Cube : public IDrawable
{
public:
    Cube(GLuint program);
    ~Cube();

    void Draw() const override;

    void SetPosition(const glm::vec3& position);
    void SetRotation(const glm::vec3& rotation);
    void SetScale(const glm::vec3& scale);
    void SetColor(const glm::vec3& rgb);

private:
    glm::vec3 m_albedo;
    glm::mat4 m_T;
    glm::mat4 m_R;
    glm::mat4 m_S;
};