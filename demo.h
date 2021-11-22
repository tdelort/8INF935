#pragma once

#define GLFW_INCLUDE_NONE

#include <Gui.h>
#include <Cube.h>
#include <ObjMesh.h>
#include <Grid.h>
#include <RigidBody.h>

#include <glm/glm.hpp>

class Demo
{
    enum class DemoState {
        MENU,
        SAMPLE_DEMO,
        COLLISION_DEMO,
        SPRING_DEMO
    };

    union DemoContext {
        struct {
            ObjMesh* mesh;
            RigidBody* rb;
        } sampleDemo;
        struct {
            Cube* car1;
            RigidBody* rb1;
            Cube* car2;
            RigidBody* rb2;
            double startTime;
            bool collided;
            bool started;
        } collisionDemo;
        struct {
            ObjMesh* mesh1;
            RigidBody* rb1;
            ObjMesh* mesh2;
            RigidBody* rb2;
        } springDemo;
    } context;

    // Cilinder coordinates
    struct Camera {
        float theta;
        float radius, height;
        glm::vec3 target;
        bool follow;
    } camera;

    double lastFrameTime;
    DemoState demoState = DemoState::MENU;
    char* meshPath;

    void CameraControls();
    void ImguiMenu();
    void ImguiSampleDemo();
    void ImguiCollisionDemo();
    void ImguiSpringDemo();

    void ClearContext(DemoState oldState);

public:
    Demo(char *path);
    void run();
};