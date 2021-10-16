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

#include "Gui.h"
#include "Cube.h"
#include "Particle.h"
#include "Shader.h"

//Vertex Shader
const char* vertexSource = R"glsl(
    #version 130

	in vec2 position;

	uniform mat4 model;
	uniform mat4 view;
	uniform mat4 proj;

	void main()
	{
		gl_Position = proj * view * model * vec4(position, 0.0, 1.0);
	}
)glsl";

//Fragment Shader
const char* fragmentSource = R"glsl(
    #version 130

	out vec4 outColor;

	void main()
	{
		outColor = vec4(1.0, 1.0, 1.0, 1.0);
	}
)glsl";

enum class State {
    SET,
    PLAY
};

int main()
{
	Gui gui;
    ImVec4 clear_color = ImVec4(0, 0, 0, 1);

    // =============== Open GL init ===================
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Putting a vertex into a buffer
    float vertices[] = { 0.0f,  0.0f,  0.0f };
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
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
    
    // Linking vertex data and attributes
    GLint positionAttrib = glGetAttribLocation(program, "position");
    glVertexAttribPointer(positionAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(positionAttrib);
    
    GLint modelUni = glGetUniformLocation(program, "model");
    GLint viewUni = glGetUniformLocation(program, "view");
    GLint projUni = glGetUniformLocation(program, "proj");

    glPointSize(5.0f);
    // ============= End Open GL init =================

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 proj = glm::mat4(1.0f);
    glUniformMatrix4fv(modelUni, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewUni, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projUni, 1, GL_FALSE, glm::value_ptr(proj));

    // Application state
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

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        switch (appState)
        {
        case State::SET:
        {
            ImGui::Begin("Config", 0, ImGuiWindowFlags_AlwaysAutoResize);

            ImGui::Text("Position Initiale");

            ImGui::SliderFloat("Px", &px, -1.0f, 1.0f); ImGui::SameLine();
            ImGui::SliderFloat("Py", &py, -1.0f, 1.0f); ImGui::SameLine();
            ImGui::SliderFloat("Pz", &pz, -1.0f, 1.0f);

            ImGui::Text("Velocite Initiale");

            ImGui::SliderFloat("Vx", &vx, -3.0f, 3.0f); ImGui::SameLine();
            ImGui::SliderFloat("Vy", &vy, -3.0f, 3.0f); ImGui::SameLine();
            ImGui::SliderFloat("Vz", &vz, -3.0f, 3.0f);
            
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
        
        // Move particle
		model = glm::mat4(1.0f);
		glm::vec3 pos = glm::vec3(particle.position().x(), particle.position().y(), particle.position().z());
		model = glm::translate(model, pos);
		glUniformMatrix4fv(modelUni, 1, GL_FALSE, glm::value_ptr(model));
        

        gui.clear(clear_color);
        glDrawArrays(GL_POINTS, 0, 1);
        gui.swapBuffers();
	}
    
    // destructor of Gui called during this return
    return 0;
}