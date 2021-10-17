#include "Camera.h"
#include <glad/glad.h>
#include <glm/glm.hpp>

Camera::Camera(glm::mat4 proj, glm::mat4 view)
    : m_proj(proj), m_view(view)
{}

glm::mat4 Camera::GetProj() const
{
    return m_proj;
}

glm::mat4 Camera::GetView() const
{
    return m_view;
}

Camera::~Camera()
{

}
