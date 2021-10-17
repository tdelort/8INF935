#include "Grid.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>


GLuint Grid::CreateProgram() const
{
    //Vertex Shader
    const char* gridVertexSource = R"glsl(
        #version 130

        in vec3 position;
        in vec3 color;

        uniform float size;
        uniform mat4 view;
        uniform mat4 proj;

        out vec3 Color;
        out vec3 ex_pos;

        void main()
        {
            Color = color;
            vec4 out_pos = proj * view * vec4(size * position, 1.0f);
            gl_Position = out_pos;
            ex_pos = position * size;
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
            float thickness = 0.005f;
            float large_thickness = 5 * thickness;
            float alpha = fract(ex_pos.x) < thickness || fract(ex_pos.z) < thickness ? 0.5f : 0.0f;
            alpha = fract((5 + ex_pos.x) / 5) < large_thickness / 5 || fract((5 + ex_pos.z) / 5) < large_thickness / 5 ? 1.0f : alpha;

            float dist_coef = 1.0f - clamp(0.025f * length(vec2(ex_pos.x, ex_pos.z)), 0.0f, 1.0f);
            
            vec3 color = Color;
            if(-large_thickness <= ex_pos.x && ex_pos.x <= large_thickness)
                color = vec3(1.0f, 0.0f, 0.0f);
            if(-large_thickness <= ex_pos.z && ex_pos.z <= large_thickness)
                color = vec3(0.0f, 0.0f, 1.0f);

            outColor = dist_coef * vec4(color, alpha);
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

Grid::Grid()
    : m_size(100.0f)
{
    GLfloat gridVertex[] = {
        -0.5f,  0.0f,  0.5f,
         0.5f,  0.0f,  0.5f,
         0.5f,  0.0f, -0.5f,
        -0.5f,  0.0f, -0.5f
    };

    GLfloat gridColors[] = {
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f
    };

    GLuint gridFaces[] = {
        0, 1, 2,
        2, 3, 0
    };
    
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    // Vertex Data
    glGenBuffers(1, &m_vertexVbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(gridVertex), gridVertex, GL_STATIC_DRAW);

    m_program = CreateProgram();
    GLint positionAttrib = glGetAttribLocation(m_program, "position");
    glVertexAttribPointer(positionAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(positionAttrib);

    // Colors Data
    glGenBuffers(1, &m_colorsVbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorsVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(gridColors), gridColors, GL_STATIC_DRAW);

    GLint colorAttrib = glGetAttribLocation(m_program, "color");
    glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(colorAttrib);

    // EBO
    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(gridFaces), gridFaces, GL_STATIC_DRAW);

    m_sizeUni = glGetUniformLocation(m_program, "size");
    m_viewUni = glGetUniformLocation(m_program, "view");
    m_projUni = glGetUniformLocation(m_program, "proj");
}

Grid::~Grid()
{
    
}

void Grid::Draw(glm::mat4 proj, glm::mat4 view) const
{
    glUseProgram(m_program);
    glBindVertexArray(m_vao);
    glUniform1f(m_sizeUni, m_size);
    glUniformMatrix4fv(m_projUni, 1, GL_FALSE, glm::value_ptr(proj));
    glUniformMatrix4fv(m_viewUni, 1, GL_FALSE, glm::value_ptr(view));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Grid::SetSize(float size)
{
    m_size = size;
}