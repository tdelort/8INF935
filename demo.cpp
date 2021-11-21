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
#include <PhysicsEngine.h>

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

void Demo::CameraControls()
{
    ImGui::Text("Camera configuration :");
    ImGui::SliderFloat("Camera theta", &camera.theta, 0, 3.14f * 2.0f);
    ImGui::SliderFloat("Camera height", &camera.height, -5, 5);
    ImGui::SliderFloat("Camera radius", &camera.radius, 1, 10);

    if (demoState == DemoState::SAMPLE_DEMO)
    {   
        ImGui::Checkbox("Follow Mesh", &camera.follow);
        if (camera.follow)
        {
            camera.target.x = context.sampleDemo.rb->GetPosition().x();
            camera.target.y = context.sampleDemo.rb->GetPosition().y();
            camera.target.z = context.sampleDemo.rb->GetPosition().z();
        }
        else
        {
            ImGui::SliderFloat("Target x", &camera.target.x, -10, 10);
            ImGui::SliderFloat("Target y", &camera.target.y, -10, 10);
            ImGui::SliderFloat("Target z", &camera.target.z, -10, 10);
        }
    }
    else if (demoState == DemoState::COLLISION_DEMO)
    {

    }
    else // DemoState::MENU
    {
        ImGui::SliderFloat("Target x", &camera.target.x, -10, 10);
        ImGui::SliderFloat("Target y", &camera.target.y, -10, 10);
        ImGui::SliderFloat("Target z", &camera.target.z, -10, 10);
    }
}

void Demo::ImguiMenu()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    ImGui::NewFrame();
    ImGui::Begin("Main Menu", 0, ImGuiWindowFlags_AlwaysAutoResize);
    CameraControls();
    ImGui::Text("Choose the demo");
    if (ImGui::Button("Sample Demo"))
        demoState = DemoState::SAMPLE_DEMO;
    ImGui::SameLine();
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
    CameraControls();
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
    CameraControls();
    if (ImGui::Button("Back"))
        demoState = DemoState::MENU;
    ImGui::End();
}


void Demo::ClearContext(DemoState oldState)
{
    switch (oldState)
    {
    case DemoState::MENU:
        break;
    case DemoState::SAMPLE_DEMO:
        delete context.sampleDemo.mesh;
        delete context.sampleDemo.rb;
        break;
    case DemoState::COLLISION_DEMO:
        break;
    default:
        break;
    }
}

Demo::Demo(char* path)
{
    meshPath = path;
}

void Demo::run()
{
    // Shared in all scenes
    Gui* gui = new Gui();
    Grid grid(Grid::CreateProgram());
    ImVec4 clear_color = ImVec4(0, 0, 0, 1);
    camera = {0.0, 5.0, 1.0, glm::vec3(0.0, 0.0, 0.0), false};
    double lastFrameTime = glfwGetTime();

	while(gui->isOpen())
    {
        gui->pollEvents();

        // ################### IMGUI ###################
        DemoState oldState = demoState;
        if (demoState == DemoState::MENU)
        {
            ImguiMenu();
        }
        else if (demoState == DemoState::SAMPLE_DEMO)
        {
            ImguiSampleDemo();
        }
        else if (demoState == DemoState::COLLISION_DEMO)
        {
            ImguiCollisionDemo();
        }

        // ################# TRANSITIONS #################
        if (demoState != oldState)
        {
            std::cout << "Transition to : ";

            ClearContext(oldState);
            PhysicsEngine::Clear();

            if (demoState == DemoState::MENU)
            {
                std::cout << "Menu" << std::endl;
            }
            else if (demoState == DemoState::SAMPLE_DEMO)
            {
                std::cout << "Sample Demo" << std::endl;

                RigidBody* rb = new RigidBody(
                    Vector3D(0, 0, 0),
                    Quaternion(1, 0, 0, 0),
                    1.0f,
                    0.99f,
                    0.99f,
                    {{0.4, 0, 0},
                    {0, 0.4, 0},
                    {0, 0, 0.4}}
                );

                ObjMesh* mesh = new ObjMesh(createProgram(), meshPath);
                mesh->SetScale(glm::vec3(0.3f));
                mesh->SetColor(glm::vec3(1.0f));
                mesh->SetPosition(glm::vec3(0, 0, 0));
                mesh->SetRotation(glm::vec3(0.0f, 30.0f, 0.0f));

                context.sampleDemo.rb = rb;
                context.sampleDemo.mesh = mesh;
                context.sampleDemo.startTime = glfwGetTime();

                PhysicsEngine::AddRigidBody(rb);
            }
            else if (demoState == DemoState::COLLISION_DEMO)
            {
                std::cout << "Collision Demo" << std::endl;
            }
            lastFrameTime = glfwGetTime();
            // clear PhysicsEngine
        }

        gui->clear(clear_color);
        glm::mat4 view = glm::lookAt(
            glm::vec3(camera.radius * cos(camera.theta), camera.height, camera.radius * sin(camera.theta)),
            camera.target,
            glm::vec3(0.0f, 1.0f, 0.0f)
        );

        int width, height;
        glfwGetWindowSize(gui->GetWindow(), &width, &height);
        glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 1.0f, 100.0f);

        if (demoState == DemoState::MENU)
        {

        }
        else if (demoState == DemoState::SAMPLE_DEMO)
        {
            double currentTime = glfwGetTime();
            if (currentTime - context.sampleDemo.startTime < 0.2f)
            { 
                std::cout << "Time : " << currentTime - context.sampleDemo.startTime << std::endl;
                context.sampleDemo.rb->AddForceAtPoint(Vector3D(0, 5, 0), Vector3D(0, 1, 1));
            }


            // ################### PHYSICS ###################
            double deltaTime = glfwGetTime() - lastFrameTime;
            lastFrameTime = glfwGetTime();
            PhysicsEngine::Update(deltaTime);

            //std::cout << "deltaTime : " << deltaTime << std::endl;
            //std::cout << "fps : " << 1 / deltaTime << std::endl;

            // ################## GRAPHICS ###################
            Vector3D r = context.sampleDemo.rb->GetRotation();
            Vector3D v = context.sampleDemo.rb->GetPosition();
            context.sampleDemo.mesh->SetPosition(glm::vec3(v.x(), v.y(), v.z()));
            context.sampleDemo.mesh->SetRotation(glm::vec3(r.x(), r.y(), r.z()));
            context.sampleDemo.mesh->Draw(proj, view);
        }
        else if (demoState == DemoState::COLLISION_DEMO)
        {
            //mesh2.Draw(proj, view);
        }

        grid.Draw(proj, view);

        gui->swapBuffers();
    }
}