#pragma once

#include <glm/glm.hpp>

class IDrawable {
public:
    virtual void Draw(glm::mat4 proj, glm::mat4 view) = 0;
};