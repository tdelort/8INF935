#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>

class Camera
{
private:
    glm::mat4 m_proj;
    glm::mat4 m_view;
public:
    Camera(glm::mat4 proj, glm::mat4 view);

    glm::mat4 GetProj() const;
    glm::mat4 GetView() const;

    ~Camera();
};
