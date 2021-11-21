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
        COLLISION_DEMO
    };

    union DemoContext {
        struct {
            ObjMesh* mesh;
            RigidBody* rb;
            double startTime;
        } sampleDemo;
    } context;

    // Cilinder coordinates
    struct Camera {
        float theta;
        float radius, height;
        glm::vec3 target;
        bool follow;
    } camera;

    DemoState demoState = DemoState::MENU;
    char* meshPath;

    void CameraControls();
    void ImguiMenu();
    void ImguiSampleDemo();
    void ImguiCollisionDemo();

    void ClearContext(DemoState oldState);

public:
    Demo(char *path);
    void run();
};