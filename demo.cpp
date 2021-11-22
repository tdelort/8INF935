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
#include <rigidbody_forces/GravityForceGenerator.h>
#include <rigidbody_forces/SpringForceGenerator.h>
#include <rigidbody_forces/AnchoredSpringForceGenerator.h>

inline float frand(int lo, int hi)
{
    return lo + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(hi-lo)));
}

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
        ImGui::Checkbox("Follow Mesh", &camera.follow);
        if (camera.follow)
        {
            camera.target.x = context.collisionDemo.rb1->GetPosition().x();
            camera.target.y = context.collisionDemo.rb1->GetPosition().y();
            camera.target.z = context.collisionDemo.rb1->GetPosition().z();
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
    ImGui::SameLine();
    if (ImGui::Button("Collision Demo"))
        demoState = DemoState::COLLISION_DEMO;
    ImGui::SameLine();
    if (ImGui::Button("Spring Demo"))
        demoState = DemoState::SPRING_DEMO;
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
    if(!context.collisionDemo.started)
    {
        if (ImGui::Button("Start"))
        {
            context.collisionDemo.started = true;
            lastFrameTime = glfwGetTime();
            context.collisionDemo.startTime = glfwGetTime();
        }
    }
    if (ImGui::Button("Back"))
        demoState = DemoState::MENU;
    ImGui::End();
}

void Demo::ImguiSpringDemo()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    ImGui::NewFrame();
    ImGui::Begin("Spring Demo", 0, ImGuiWindowFlags_AlwaysAutoResize);
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
        delete context.collisionDemo.car1;
        delete context.collisionDemo.rb1;
        delete context.collisionDemo.car2;
        delete context.collisionDemo.rb2;
        break;
    case DemoState::SPRING_DEMO:
        delete context.springDemo.mesh1;
        delete context.springDemo.rb1;
        delete context.springDemo.mesh2;
        delete context.springDemo.rb2;
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
        else if (demoState == DemoState::SPRING_DEMO)
        {
            ImguiSpringDemo();
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
                    Vector3D(0, 1, 0),
                    Quaternion(1, 0, 0, 0),
                    1.0f, 0.99f, 0.99f,
                    {{2, 0, 0}, {0, 2, 0}, {0, 0, 2}}
                );

                ObjMesh* mesh = new ObjMesh(createProgram(), meshPath);
                mesh->SetScale(glm::vec3(0.3f));
                mesh->SetColor(glm::vec3(1.0f));

                context.sampleDemo.rb = rb;
                context.sampleDemo.mesh = mesh;

                PhysicsEngine::AddRigidBody(rb);
                PhysicsEngine::AddRigidBodyForceGenerator(rb, new GravityForceGenerator(Vector3D(0, -9.81, 0)));
            }
            else if (demoState == DemoState::COLLISION_DEMO)
            {
                std::cout << "Collision Demo" << std::endl;

                Vector3D pos1(2, 0, 0.25);
                RigidBody* rb1 = new RigidBody( 
                    pos1,
                    Quaternion(1, 0, 0, 0),
                    1.0f, 0.99f, 0.99f,
                    {{0.4, 0, 0}, {0, 0.4, 0}, {0, 0, 0.4}}
                );

                Cube* cube1 = new Cube(createProgram());
                cube1->SetScale(glm::vec3(1.0f, 0.2f, 0.5f));
                cube1->SetColor(glm::vec3(7.0f, 1.0f, 1.0f));

                Vector3D pos2(-2, 0, 0);
                RigidBody* rb2 = new RigidBody(
                    pos2,
                    Quaternion(1, 0, 0, 0),
                    4.0f, 0.99f, 0.99f,
                    {{0.4, 0, 0}, {0, 0.4, 0}, {0, 0, 0.4}}
                );

                Cube* cube2 = new Cube(createProgram());
                cube2->SetScale(glm::vec3(1.0f, 0.4f, 0.5f));
                cube2->SetColor(glm::vec3(1.0f, 7.0f, 7.0f));

                context.collisionDemo.car1 = cube1;
                context.collisionDemo.rb1 = rb1;
                context.collisionDemo.car2 = cube2;
                context.collisionDemo.rb2 = rb2;
                context.collisionDemo.startTime = glfwGetTime();
                context.collisionDemo.collided = false;
                context.collisionDemo.started = false;

                PhysicsEngine::AddRigidBody(rb1);
                PhysicsEngine::AddRigidBody(rb2);
            }
            else if (demoState == DemoState::SPRING_DEMO)
            {
                std::cout << "Spring Demo" << std::endl;

                Vector3D anchor(0, 4, 0);

                context.springDemo.rb1 = new RigidBody(
                    Vector3D(0, 3, 0),
                    Quaternion(1, 0, 0, 0),
                    1.0f, 0.90f, 0.90f,
                    {{2, 0, 0}, {0, 2, 0}, {0, 0, 2}}
                );

                context.springDemo.mesh1 = new ObjMesh(createProgram(), meshPath);
                context.springDemo.mesh1->SetScale(glm::vec3(0.2f));
                context.springDemo.mesh1->SetColor(glm::vec3(1.0f));

                context.springDemo.rb2 = new RigidBody(
                    Vector3D(0, 2, 0),
                    Quaternion(1, 0, 0, 0),
                    1.0f, 0.90f, 0.90f,
                    {{2, 0, 0}, {0, 2, 0}, {0, 0, 2}}
                );

                context.springDemo.mesh2 = new ObjMesh(createProgram(), meshPath);
                context.springDemo.mesh2->SetScale(glm::vec3(0.2f));
                context.springDemo.mesh2->SetColor(glm::vec3(1.0f));

                PhysicsEngine::AddRigidBody(context.springDemo.rb1);
                PhysicsEngine::AddRigidBody(context.springDemo.rb2);
                PhysicsEngine::AddRigidBodyForceGenerator(
                    context.springDemo.rb1, 
                    new AnchoredSpringForceGenerator(anchor, Vector3D(0.15, 0.15, 0.15), 8, 0.75)
                );
                PhysicsEngine::AddRigidBodyForceGenerator(
                    context.springDemo.rb2, 
                    new SpringForceGenerator(context.springDemo.rb1, Vector3D(-0.15, 0.15, -0.15), Vector3D(0, 0.15, 0.15), 10, 0.5)
                );
                PhysicsEngine::AddRigidBodyForceGenerator(
                    context.springDemo.rb1,
                    new GravityForceGenerator(Vector3D(0, -9.81, 0))
                );
                PhysicsEngine::AddRigidBodyForceGenerator(
                    context.springDemo.rb2,
                    new GravityForceGenerator(Vector3D(0, -9.81, 0))
                );
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
            Vector3D pos = context.sampleDemo.rb->GetPosition();
            if (pos.y() < 0.0f)
            {
                float intensity = 50 * (1 / 0.1f); // Impulse
                Vector3D point = Vector3D(frand(-1, 1), 0.0f, frand(-1, 1));
                context.sampleDemo.rb->AddForceAtPoint(Vector3D(0, intensity, 0), point);
            }


            // ################### PHYSICS ###################
            double deltaTime = glfwGetTime() - lastFrameTime;
            lastFrameTime = glfwGetTime();
            PhysicsEngine::Update(deltaTime);

            // ################## GRAPHICS ###################
            Vector3D r = context.sampleDemo.rb->GetRotation();
            Vector3D v = context.sampleDemo.rb->GetPosition();
            context.sampleDemo.mesh->SetPosition(glm::vec3(v.x(), v.y(), v.z()));
            context.sampleDemo.mesh->SetRotation(glm::vec3(r.x(), r.y(), r.z()));
            context.sampleDemo.mesh->Draw(proj, view);
        }
        else if (demoState == DemoState::COLLISION_DEMO)
        {
            if(context.collisionDemo.started)
            {
                double currentTime = glfwGetTime();
                Vector3D pos1 = context.collisionDemo.rb1->GetPosition();
                Vector3D pos2 = context.collisionDemo.rb2->GetPosition();
                if (currentTime - context.collisionDemo.startTime < 0.1f)
                { 
                    context.collisionDemo.rb1->AddForce(Vector3D(-30, 0, 0));
                    context.collisionDemo.rb2->AddForce(Vector3D(30, 0, 0));
                }
                else if (!context.collisionDemo.collided && abs(pos1.x() - pos2.x()) < 1.0f)
                {
                    context.collisionDemo.collided = true;
                    float intensity = 30.0f * 1.5f * (1.0f / 0.1f);
                    Vector3D dir = pos2 - pos1;
                    dir.normalize();
                    Vector3D force = dir * intensity;
                    context.collisionDemo.rb1->AddForceAtBodyPoint(-force, Vector3D( 0.5, 0, -0.125));
                    context.collisionDemo.rb2->AddForceAtBodyPoint(force, Vector3D(-0.5, 0, 0.125));
                }
            }
            // ################### PHYSICS ###################
            double deltaTime = glfwGetTime() - lastFrameTime;
            lastFrameTime = glfwGetTime();
            PhysicsEngine::Update(deltaTime);

            // ################## GRAPHICS ###################
            Vector3D r = context.collisionDemo.rb1->GetRotation();
            Vector3D v = context.collisionDemo.rb1->GetPosition();
            context.collisionDemo.car1->SetPosition(glm::vec3(v.x(), v.y(), v.z()));
            context.collisionDemo.car1->SetRotation(glm::vec3(r.x(), r.y(), r.z()));

            r = context.collisionDemo.rb2->GetRotation();
            v = context.collisionDemo.rb2->GetPosition();
            context.collisionDemo.car2->SetPosition(glm::vec3(v.x(), v.y(), v.z()));
            context.collisionDemo.car2->SetRotation(glm::vec3(r.x(), r.y(), r.z()));

            context.collisionDemo.car1->Draw(proj, view);
            context.collisionDemo.car2->Draw(proj, view);
        }
        else if (demoState == DemoState::SPRING_DEMO)
        {
            // ################### PHYSICS ###################
            double deltaTime = glfwGetTime() - lastFrameTime;
            lastFrameTime = glfwGetTime();
            PhysicsEngine::Update(deltaTime);

            // ################## GRAPHICS ###################
            Vector3D r = context.springDemo.rb1->GetRotation();
            Vector3D v = context.springDemo.rb1->GetPosition();
            context.springDemo.mesh1->SetPosition(glm::vec3(v.x(), v.y(), v.z()));
            context.springDemo.mesh1->SetRotation(glm::vec3(r.x(), r.y(), r.z()));

            r = context.springDemo.rb2->GetRotation();
            v = context.springDemo.rb2->GetPosition();
            context.springDemo.mesh2->SetPosition(glm::vec3(v.x(), v.y(), v.z()));
            context.springDemo.mesh2->SetRotation(glm::vec3(r.x(), r.y(), r.z()));

            context.springDemo.mesh1->Draw(proj, view);
            context.springDemo.mesh2->Draw(proj, view);
        }

        grid.Draw(proj, view);

        gui->swapBuffers();
    }
}