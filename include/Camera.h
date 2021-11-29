#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>

// Camera singleton
class Camera
{
private:
    glm::mat4 proj;
    glm::mat4 view;

    Camera() = default;
public:
    Camera(const Camera&) = delete;
    Camera& operator=(const Camera&) = delete;
    Camera(const Camera&&) = delete;
    Camera& operator=(const Camera&&) = delete;

    static Camera& instance()
    {
        static Camera instance;
        return instance;
    }

    static void setProj(const glm::mat4& proj)
    {
        instance().proj = proj;
    }

    static void setView(const glm::mat4& view)
    {
        instance().view = view;
    }

    static const glm::mat4& getProj()
    {
        return instance().proj;
    }

    static const glm::mat4& getView()
    {
        return instance().view;
    }
};
