#include "Grid.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <array>

GLuint Grid::CreateProgram()
{
    //Vertex Shader
    const char* gridVertexSource = R"glsl(
        #version 130

        in vec3 position;
        in vec3 color;

        uniform mat4 view;
        uniform mat4 proj;

        out vec3 Color;
        out vec3 ex_pos;

        void main()
        {
            Color = color;
            gl_Position = proj * view * vec4(position, 1.0);
            ex_pos = position;
        }
    )glsl";

    //Fragment Shader
    const char* gridFragmentSource = R"glsl(
        #version 130

        in vec3 Color;
        in vec3 ex_pos;

        out vec4 outColor;

        void main()
        {
            float dist_coef = 1.0f - clamp(0.1f * length(vec2(ex_pos.x, ex_pos.z)), 0.0f, 1.0f);
            vec3 c = Color;
            if(ex_pos.x == 0)
                c = vec3(0.0, 0.0, 1.0);
            else if(ex_pos.z == 0)
                c = vec3(1.0, 0.0, 0.0);
            outColor = vec4(c, dist_coef);
        }
    )glsl";

    // Creating Vertex shader
    GLint status;
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &gridVertexSource, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    std::cout << "Vertex shader compile status : " << status << std::endl;

    // Creating Fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &gridFragmentSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    std::cout << "Fragment shader compile status : " << status << std::endl;
    
    // Creating shader program and linking it
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    glUseProgram(program);
    return program;
}

Grid::Grid(GLuint program)
    : IDrawable(program)
{
    GLfloat gridVertex[4 * size * 3];
    GLfloat gridColors[4 * size * 3];
    GLuint gridEbo[4 * size * 2];
    for(int i = 0; i < size; i++)
    {
        float f = (float)(i - size/2);
        int I = 4 * i * 3;
        // from -x to +x
        gridVertex[I] = f;
        gridVertex[I+1] = 0.0f;
        gridVertex[I+2] = (float)size/2;
        gridColors[I] = 1.0f;
        gridColors[I+1] = 1.0f;
        gridColors[I+2] = 1.0f;
        gridEbo[4*i] = 4 * i;

        gridVertex[I+3] = f;
        gridVertex[I+4] = 0.0f;
        gridVertex[I+5] = -(float)size/2;
        gridColors[I+3] = 1.0f;
        gridColors[I+4] = 1.0f;
        gridColors[I+5] = 1.0f;
        gridEbo[4*i + 1] = 4*i + 1;
        
        // from -z to +z
        gridVertex[I+6] = (float)size/2;
        gridVertex[I+7] = 0.0f;
        gridVertex[I+8] = f;
        gridColors[I+6] = 1.0f;
        gridColors[I+7] = 1.0f;
        gridColors[I+8] = 1.0f;
        gridEbo[4*i + 2] = 4*i + 2;

        gridVertex[I+9] = -(float)size/2;
        gridVertex[I+10] = 0.0f;
        gridVertex[I+11] = f;
        gridColors[I+9] = 1.0f;
        gridColors[I+10] = 1.0f;
        gridColors[I+11] = 1.0f;
        gridEbo[4*i + 3] = 4*i + 3;
    }

    Init(gridVertex, sizeof(gridVertex), gridColors, sizeof(gridColors), gridEbo, sizeof(gridEbo));   

    m_viewUni = glGetUniformLocation(m_program, "view");
    m_projUni = glGetUniformLocation(m_program, "proj");
}

Grid::~Grid()
{
    
}

void Grid::Draw(const glm::mat4& proj, const glm::mat4& view) const
{
    glUseProgram(m_program);
    glBindVertexArray(m_vao);
    glUniformMatrix4fv(m_projUni, 1, GL_FALSE, glm::value_ptr(proj));
    glUniformMatrix4fv(m_viewUni, 1, GL_FALSE, glm::value_ptr(view));
    glDrawElements(GL_LINES, 4 * size * 2, GL_UNSIGNED_INT, 0);
}