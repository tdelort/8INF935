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
#include "Particle.h"

//Vertex Shader
const char* vertexSource = R"glsl(
    #version 130

	in vec3 position;
    in vec3 color;

    out vec3 Color;

	uniform mat4 model;
	uniform mat4 view;
	uniform mat4 proj;
    uniform vec3 albedo;

	void main()
	{
        //Color = color;
        Color = albedo;
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

enum class State {
    SET,
    PLAY
};

int main()
{
	Gui gui;
    ImVec4 clear_color = ImVec4(0, 0, 0, 1);

    GLuint program = createProgram();

    Cube cube(program);
    cube.SetScale(glm::vec3(0.1f));
    cube.SetColor(glm::vec3(0.0, 0.7, 0.6));

    Grid grid;

    State appState = State::SET;
    Particle particle;
    particle.setMass(1);
    particle.addForce(Vector3D(0, -9.81f, 0));

    double lastFrameTime;

	float px, py, pz, vx, vy, vz;
	px = py = pz = vx = vy = vz = 0;
	while (gui.isOpen())
	{
        gui.pollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        switch (appState)
        {
        case State::SET:
        {
            ImGui::Begin("Config", 0, ImGuiWindowFlags_AlwaysAutoResize);

            ImGui::Text("Position Initiale");

            ImGui::SliderFloat("Px", &px, -5.0f, 5.0f); ImGui::SameLine();
            ImGui::SliderFloat("Py", &py, -5.0f, 5.0f); ImGui::SameLine();
            ImGui::SliderFloat("Pz", &pz, -5.0f, 5.0f);

            ImGui::Text("Velocite Initiale");

            ImGui::SliderFloat("Vx", &vx, -5.0f, 5.0f); ImGui::SameLine();
            ImGui::SliderFloat("Vy", &vy, -5.0f, 5.0f); ImGui::SameLine();
            ImGui::SliderFloat("Vz", &vz, -5.0f, 5.0f);
            
            particle.setPosition(Vector3D(px, py, pz));
            particle.setVelocity(Vector3D(vx, vy, vz));

            if (ImGui::Button("Start"))
            {
                appState = State::PLAY;
                lastFrameTime = glfwGetTime();
            }
            ImGui::End();
            break;
        }
        case State::PLAY:
        {
            ImGui::Begin("Controls", 0, ImGuiWindowFlags_AlwaysAutoResize);
            ImGui::Text("Press Stop to stop the simulation");
            if (ImGui::Button("Stop"))
            {
                appState = State::SET;
            }
            ImGui::End();

            // Computation on Particle
            double deltaTime = glfwGetTime() - lastFrameTime;
            lastFrameTime = glfwGetTime();

            particle.Integrate(deltaTime);
            break;
        }
        default:
            break;
        }
        

        gui.clear(clear_color);
        glm::mat4 view = glm::lookAt(
            glm::vec3(5.0f, 1.0f, 5.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );

        int width, height;
        glfwGetWindowSize(gui.GetWindow(), &width, &height);
        glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 1.0f, 100.0f);

		cube.SetPosition(glm::vec3(particle.position().x(), particle.position().y(), particle.position().z()));

        cube.Draw(proj, view);
        grid.Draw(proj, view);
        gui.swapBuffers();
	}
    
    // destructor of Gui called during this return
    return 0;
}
