#define GLFW_INCLUDE_NONE

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glad/glad.h>

#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include <iostream>

#include "Gui.h"
#include "Cube.h"
#include "Grid.h"

//Vertex Shader
const char* vertexSource = R"glsl(
    #version 130

	in vec3 position;
    in vec3 color;

    out vec3 Color;

	uniform mat4 model;
	uniform mat4 view;
	uniform mat4 proj;

	void main()
	{
        Color = color;
		gl_Position = proj * view * model * vec4(position, 1.0);
	}
)glsl";

//Fragment Shader
const char* fragmentSource = R"glsl(
    #version 130

    in vec3 Color;

	out vec4 outColor;

	void main()
	{
		outColor = vec4(Color, 1.0);
	}
)glsl";

GLuint createProgram()
{
    // Creating Vertex shader
    GLint status;
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    std::cout << "Vertex shader compile status : " << status << std::endl;

    // Creating Fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
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

int main()
{
	Gui gui;
    ImVec4 clear_color = ImVec4(0, 0, 0, 1);

    GLuint program = createProgram();

    Cube cube(program);

    Grid grid;

    double startTime = glfwGetTime();
	while (gui.isOpen())
	{
        gui.pollEvents();
        gui.clear(clear_color);

        double time = glfwGetTime() - startTime;
        time /= 1.0;
        glm::mat4 view = glm::lookAt(
            glm::vec3(5 * std::cos(time), 1.0f, 5 * std::sin(time)),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );

        //std::cout << glm::to_string(view) << std::endl;
        int width, height;
        glfwGetWindowSize(gui.GetWindow(), &width, &height);
        glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 1.0f, 100.0f);

        cube.Draw(proj, view);
        grid.Draw(proj, view);
        gui.swapBuffers();
	}
    
    // destructor of Gui called during this return
    return 0;
}
