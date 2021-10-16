
#include <glad/glad.h>

#include <vector>
#include <iostream>

class Shader
{
public:
    Shader(std::istream& vertexIn, std::istream& fragmentIn);
    ~Shader();
    void addGeometryShader(std::istream& geometryIn);
private:
    GLuint m_vertexShader, m_fragmentShader, m_geometryShader;
    GLuint m_program;
};