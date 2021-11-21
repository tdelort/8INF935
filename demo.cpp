#define GLFW_INCLUDE_NONE

#include "demo.h"

// IMGUI
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

// GLAD
#include <glad/glad.h>

// GLFW
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

// STD Lib
#include <iostream>
#include <cstdlib>

// Physics Engine
#include <Gui.h>
#include <Cube.h>
#include <ObjMesh.h>
#include <Grid.h>
#include <Shader.h>
#include <RigidBody.h>

GLuint createProgram()
{
    // Creating Vertex shader
    GLint status;
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    std::cout << "Vertex shader compile status : " << status << std::endl;

    // Creating Geometry shader
    GLuint geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geometryShader, 1, &geometrySource, NULL);
    glCompileShader(geometryShader);

    glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &status);
    std::cout << "Geometry shader compile status : " << status << std::endl;

    // Creating Fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    std::cout << "Fragment shader compile status : " << status << std::endl;
    
    // Creating shader program and linking it
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, geometryShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    glUseProgram(program);
    return program;
}

void Demo::ImguiMenu()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    ImGui::NewFrame();
    ImGui::Begin("Main Menu", 0, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::Text("Choose the demo");
    if (ImGui::Button("Sample Demo"))
        demoState = DemoState::SAMPLE_DEMO;
    if (ImGui::Button("Collision Demo"))
        demoState = DemoState::COLLISION_DEMO;
    ImGui::End();
}

void Demo::ImguiSampleDemo()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    ImGui::NewFrame();
    ImGui::Begin("Sample Demo", 0, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::SliderFloat("Camera rotation", &r, 0, 3.14f * 2.0f);
    if (ImGui::Button("Back"))
        demoState = DemoState::MENU;
    ImGui::End();
}

void Demo::ImguiCollisionDemo()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    ImGui::NewFrame();
    ImGui::Begin("Collision Demo", 0, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::SliderFloat("Camera rotation", &r, 0, 3.14f * 2.0f);
    if (ImGui::Button("Back"))
        demoState = DemoState::MENU;
    ImGui::End();
}

Demo::Demo(char* path)
{
    meshPath = path;
}

void Demo::run()
{
    Gui gui;
    Grid grid(Grid::CreateProgram());
    ObjMesh mesh(createProgram(), meshPath);
    mesh.SetScale(glm::vec3(0.3f));
    mesh.SetColor(glm::vec3(1.0f));
    mesh.SetPosition(glm::vec3(0, 0, 0));
    mesh.SetRotation(glm::vec3(0.0f, 30.0f, 0.0f));

    RigidBody rb = new RigidBody();
    rb.AddForce(glm::vec3(0, -9.81f, 0));

    PhysicsEngine::AddRigidBody(&rb);

    ObjMesh mesh2(createProgram(), meshPath);
    mesh2.SetScale(glm::vec3(0.3f));
    mesh2.SetColor(glm::vec3(1.0f));
    mesh2.SetPosition(glm::vec3(1, 0, 0));
    mesh2.SetRotation(glm::vec3(0.0f, 30.0f, 0.0f));

    ImVec4 clear_color = ImVec4(0, 0, 0, 1);
    r = 0;

    double lastFrameTime = glfwGetTime();

	while(gui.isOpen())
    {
        gui.pollEvents();

        // ################### IMGUI ###################
        if (demoState == DemoState::MENU)
            ImguiMenu();
        else if (demoState == DemoState::SAMPLE_DEMO)
            ImguiSampleDemo();
        else if (demoState == DemoState::COLLISION_DEMO)
            ImguiCollisionDemo();

        // ################### PHYSICS ###################
        double deltaTime = glfwGetTime() - lastFrameTime;
        lastFrameTime = glfwGetTime();
        PhysicsEngine::Update(deltaTime);

        gui.clear(clear_color);
        glm::mat4 view = glm::lookAt(
            glm::vec3(5.0f * cos(r), 1.0f, 5.0f * sin(r)),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );

        int width, height;
        glfwGetWindowSize(gui.GetWindow(), &width, &height);
        glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 1.0f, 100.0f);

        Vector3D r = rb->GetRotation();
        Vector3D v = rb->GetPosition();
        mesh.SetPosition(glm::vec3(v.x(), v.y(), v.z()));
        mesh.SetRotation(glm::vec3(r.x(), r.y(), r.z()));
        mesh.Draw(proj, view);
        //mesh2.Draw(proj, view);
        grid.Draw(proj, view);
        gui.swapBuffers();
    }
}