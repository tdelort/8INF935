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
#include <GameObject.h>
#include <PhysicsEngine.h>
#include <rigidbody_forces/GravityForceGenerator.h>
#include <rigidbody_forces/SpringForceGenerator.h>
#include <rigidbody_forces/AnchoredSpringForceGenerator.h>

#include <Camera.h>

inline float frand(int lo, int hi)
{
    return lo + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(hi-lo)));
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
            camera.target.x = context.sampleDemo.sphere1->rb->GetPosition().x();
            camera.target.y = context.sampleDemo.sphere1->rb->GetPosition().y();
            camera.target.z = context.sampleDemo.sphere1->rb->GetPosition().z();
        }
        else
        {
            ImGui::SliderFloat("Target x", &camera.target.x, -10, 10);
            ImGui::SliderFloat("Target y", &camera.target.y, -10, 10);
            ImGui::SliderFloat("Target z", &camera.target.z, -10, 10);
        }
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

void Demo::ClearContext(DemoState oldState)
{
    switch (oldState)
    {
    case DemoState::SAMPLE_DEMO:
        delete context.sampleDemo.sphere1;
        delete context.sampleDemo.sphere2;
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
    camera = {3.14 * 0.5, 5.0, 2.5, glm::vec3(0.0, 0.0, 0.0), false};
    lastFrameTime = glfwGetTime();

	while(gui->isOpen())
    {
        gui->pollEvents();

        // ################### IMGUI ###################
        DemoState oldState = demoState;
        switch(demoState)
        {
            case DemoState::MENU: ImguiMenu(); break;
            case DemoState::SAMPLE_DEMO: ImguiSampleDemo(); break;
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

                RigidBody* rb1 = new RigidBody(
                    Vector3D(0, 5, 0),
                    Quaternion(1, 0, 0, 0),
                    1.0f, 0.99f, 0.99f,
                    {{2, 0, 0}, {0, 2, 0}, {0, 0, 2}}
                );

                ObjMesh* mesh1 = new ObjMesh(createProgram(false), meshPath);
                mesh1->SetScale(glm::vec3(0.3f));
                mesh1->SetColor(glm::vec3(1.0f));

                Primitive* col1 = new Sphere(0.5f);
                col1->offset = Matrix3x4::Identity();
                col1->rb = rb1;

                context.sampleDemo.sphere1 = new GameObject(rb1, col1, mesh1);

                RigidBody* rb2 = new RigidBody(
                    Vector3D(0, 0, 0),
                    Quaternion(1, 0, 0, 0),
                    1.0f, 0.99f, 0.99f,
                    {{2, 0, 0}, {0, 2, 0}, {0, 0, 2}}
                );

                ObjMesh* mesh2 = new ObjMesh(createProgram(false), meshPath);
                mesh2->SetScale(glm::vec3(0.3f));
                mesh2->SetColor(glm::vec3(1.0f));

                Primitive* col2 = new Sphere(0.5f);
                col2->offset = Matrix3x4::Identity();
                col2->rb = rb2;

                context.sampleDemo.sphere2 = new GameObject(rb2, col2, mesh2);

                PhysicsEngine::AddGameObject(context.sampleDemo.sphere1);
                PhysicsEngine::AddGameObject(context.sampleDemo.sphere2);
                PhysicsEngine::AddRigidBodyForceGenerator(rb1, new GravityForceGenerator(Vector3D(0, -9.81, 0)));
            }
            lastFrameTime = glfwGetTime();
            // clear PhysicsEngine
        }

        gui->clear(clear_color);
        Camera::setView(glm::lookAt(
            glm::vec3(camera.radius * cos(camera.theta), camera.height, camera.radius * sin(camera.theta)),
            camera.target,
            glm::vec3(0.0f, 1.0f, 0.0f)
        ));

        int width, height;
        glfwGetWindowSize(gui->GetWindow(), &width, &height);
        Camera::setProj(glm::perspective(glm::radians(45.0f), (float)width / (float)height, 1.0f, 100.0f));

        if (demoState == DemoState::SAMPLE_DEMO)
            SampleDemo();

        grid.Draw();
        gui->swapBuffers();
    }
}

void Demo::SampleDemo()
{
    // ################### PHYSICS ###################
    double deltaTime = glfwGetTime() - lastFrameTime;
    lastFrameTime = glfwGetTime();
    PhysicsEngine::Update(deltaTime);

    // ################## GRAPHICS ###################
    context.sampleDemo.sphere1->drawable->SetPosition(context.sampleDemo.sphere1->rb->GetPosition());
    context.sampleDemo.sphere1->drawable->SetRotation(context.sampleDemo.sphere1->rb->GetRotation());
    context.sampleDemo.sphere1->drawable->Draw();

    context.sampleDemo.sphere2->drawable->SetPosition(context.sampleDemo.sphere2->rb->GetPosition());
    context.sampleDemo.sphere2->drawable->SetRotation(context.sampleDemo.sphere2->rb->GetRotation());
    context.sampleDemo.sphere2->drawable->Draw();

#ifdef OCTREE_DEBUG
    PhysicsEngine::DrawOctree();
#endif
}
