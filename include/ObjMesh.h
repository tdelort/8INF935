#pragma once

#include "IDrawable.h"

#include <glad/glad.h>

#include <glm/glm.hpp>

#include <string>

class ObjMesh : public IDrawable
{
public:
    ObjMesh();
    ObjMesh(GLuint program, const std::string& fileName);
    ~ObjMesh();

    void Draw(const glm::mat4& proj, const glm::mat4& view) const override;

    void SetPosition(const glm::vec3& position);
    void SetRotation(const glm::vec3& rotation);
    void SetScale(const glm::vec3& scale);
    void SetColor(const glm::vec3& rgb);

private:
    unsigned int m_numIndices;

    glm::vec3 m_albedo;
    glm::mat4 m_T;
    glm::mat4 m_R;
    glm::mat4 m_S;
};