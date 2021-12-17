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
#include <glm/gtx/quaternion.hpp>

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

void Demo::OnCollision(Contact* data)
{
    std::cout << "Collision" << std::endl;
    context.running = false;
    lastContacts.push_back(data);
}

void Demo::CameraControls()
{
    ImGui::Text("Camera configuration :");
    ImGui::SliderFloat("Camera theta", &camera.theta, 0, 3.14f * 2.0f);
    ImGui::SliderFloat("Camera height", &camera.height, -5, 5);
    ImGui::SliderFloat("Camera radius", &camera.radius, 1, 10);

    ImGui::SliderFloat("Target x", &camera.target.x, -10, 10);
    ImGui::SliderFloat("Target y", &camera.target.y, -10, 10);
    ImGui::SliderFloat("Target z", &camera.target.z, -10, 10);
}

void Demo::ImguiMenu()
{
    ImGui::Begin("Main Menu", 0, ImGuiWindowFlags_AlwaysAutoResize);
    CameraControls();
    ImGui::Text("Choose the demo");
    if (ImGui::Button("Sphere Sphere"))
        demoState = DemoState::SPHERE_SPHERE;
    ImGui::SameLine();
    if (ImGui::Button("Box Plane"))
        demoState = DemoState::BOX_PLANE;
    ImGui::End();
}

void Demo::ImguiDemo()
{
    ImGui::Begin("Sphere Sphere", 0, ImGuiWindowFlags_AlwaysAutoResize);
    CameraControls();
    if (ImGui::Button("Back"))
        demoState = DemoState::MENU;
    ImGui::Checkbox("Running", &context.running);
    ImGui::End();
}

void Demo::ClearContext()
{
    delete context.obj1->rb;
    delete context.obj1->drawable;
    delete context.obj1->collider;
    delete context.obj2->rb;
    delete context.obj2->drawable;
    delete context.obj2->collider;
}

GameObject* Demo::CreateObject(const Vector3D& position, Primitive::Type type)
{   
    Quaternion rotation(1, 0, 0, 0);
    IDrawable* drawable; 
    Primitive* col;
    switch(type)
    {
        case Primitive::Type::SPHERE:
        {
            ObjMesh* mesh = new ObjMesh(createProgram(true), MeshPath::sphere);
            mesh->SetScale(glm::vec3(1));
            mesh->SetColor(glm::vec3(1.0f));
            drawable = static_cast<IDrawable*>(mesh);
            col = new Sphere(0.5f);
            break;
        }
        case Primitive::Type::PLANE:
        {
            Cube* cube = new Cube(createProgram(false));
            cube->SetScale(glm::vec3(10, 0.01f, 10));
            cube->SetColor(glm::vec3(1.0f));
            drawable = static_cast<IDrawable*>(cube);
            Vector3D n = -position.normalize();
            col = new Plane(n, position.norm());

            rotation = Quaternion::AngleTo(Vector3D(0,1,0), n);

            break;
        }
        case Primitive::Type::BOX:
        {
            Vector3D size(2, 1, 1.5f);
            Cube* cube = new Cube(createProgram(true));
            cube->SetScale(size);
            cube->SetColor(glm::vec3(1.0f));

            Vector3D random = Vector3D(frand(-1, 1), frand(-1, 1), frand(-1, 1));
            rotation = Quaternion::AngleTo(Vector3D(1,0,0), random);

            drawable = static_cast<IDrawable*>(cube);
            col = new Box(size / 2.0f);
        }
    }

    RigidBody* rb = new RigidBody(position, rotation, 1.0f, 0.99f, 0.99f, {{2, 0, 0}, {0, 2, 0}, {0, 0, 2}});
    rb->onCollision = [this](Contact* contact){ OnCollision(contact); };

    col->offset = Matrix3x4::Identity();
    col->rb = rb;

    return new GameObject(rb, col, drawable);
}

Demo::Demo()
{ }

void Demo::run()
{
    // Shared in all scenes
    Gui* gui = new Gui();
    Grid grid(Grid::CreateProgram());
    ImVec4 clear_color = ImVec4(0, 0, 0, 1);
    camera = {3.14 * 0.5, 5.0, 2.5, glm::vec3(0.0, 0.0, 0.0), false};
    lastFrameTime = glfwGetTime();

    DemoState oldState = demoState;
	while(gui->isOpen())
    {
        gui->pollEvents();
        gui->clear(clear_color);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // ################### IMGUI ###################
        oldState = demoState;
        switch(demoState)
        {
            case DemoState::MENU: ImguiMenu(); break;
            default: ImguiDemo(); break;
        }

        // ################# TRANSITIONS #################
        if (demoState != oldState)
        {
            std::cout << "Transition to : ";

            if (demoState == DemoState::MENU)
            {
                ClearContext();
                PhysicsEngine::Clear();
                lastContacts.clear();
                std::cout << "Menu" << std::endl;
                context.running = true;
            }
            else 
            {
                // Demo initialization
                switch(demoState)
                {
                    case DemoState::SPHERE_SPHERE:
                        std::cout << "Sphere Sphere" << std::endl;
                        context.obj1 = CreateObject(Vector3D(0, 0, 0), Primitive::Type::SPHERE);
                        context.obj2 = CreateObject(Vector3D(0.5, 3, 0.5), Primitive::Type::SPHERE);
                        PhysicsEngine::AddRigidBodyForceGenerator(context.obj2->rb, new GravityForceGenerator(Vector3D(0, -9.81, 0)));
                        break;
                    case DemoState::BOX_PLANE:
                        std::cout << "Box Plane" << std::endl;
                        context.obj1 = CreateObject(Vector3D(1, -1, 0), Primitive::Type::PLANE);
                        context.obj2 = CreateObject(Vector3D(0.5, 1, 0), Primitive::Type::BOX);
                        PhysicsEngine::AddRigidBodyForceGenerator(context.obj2->rb, new GravityForceGenerator(Vector3D(0, -9.81, 0)));
                        break;
                    default:
                        std::cout << "Unknown" << std::endl;
                        break;
                }

                PhysicsEngine::AddGameObject(context.obj1);
                PhysicsEngine::AddGameObject(context.obj2);
            }
            lastFrameTime = glfwGetTime();
            // clear PhysicsEngine
        }

        Camera::setView(glm::lookAt(
            glm::vec3(camera.radius * cos(camera.theta), camera.height, camera.radius * sin(camera.theta)),
            camera.target,
            glm::vec3(0.0f, 1.0f, 0.0f)
        ));

        int width, height;
        glfwGetWindowSize(gui->GetWindow(), &width, &height);
        Camera::setProj(glm::perspective(glm::radians(45.0f), (float)width / (float)height, 1.0f, 100.0f));

        if(demoState != DemoState::MENU)
            Draw();

        grid.Draw();

        gui->swapBuffers();
    }
}

void Demo::Draw()
{
    // ################### PHYSICS ###################
    double deltaTime = glfwGetTime() - lastFrameTime;
    lastFrameTime = glfwGetTime();
    if(context.running)
    {
        lastContacts.clear();
        PhysicsEngine::Update(deltaTime);
    }
    else
    {
        for(auto c : lastContacts)
            c->Draw();
    }

    // ################## GRAPHICS ###################
    context.obj1->drawable->SetPosition(context.obj1->rb->GetPosition());
    context.obj1->drawable->SetRotation(context.obj1->rb->GetRotation());
    context.obj1->drawable->Draw();

    context.obj2->drawable->SetPosition(context.obj2->rb->GetPosition());
    context.obj2->drawable->SetRotation(context.obj2->rb->GetRotation());
    context.obj2->drawable->Draw();
#ifdef OCTREE_DEBUG
    PhysicsEngine::DrawOctree();
#endif
}
