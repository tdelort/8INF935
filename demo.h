#pragma once

#define GLFW_INCLUDE_NONE

#include <Gui.h>
#include <Cube.h>
#include <ObjMesh.h>
#include <Grid.h>
#include <RigidBody.h>
#include <GameObject.h>
#include <Camera.h>

#include <glm/glm.hpp>

class Demo
{
    enum class DemoState {
        MENU,
        SAMPLE_DEMO,
    };

    union DemoContext {
        struct {
            GameObject* sphere1;
            GameObject* sphere2;
        } sampleDemo;
    } context;

    // Cilinder coordinates
    struct CameraData {
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

    void SampleDemo();
    void CollisionDemo();
    void SpringDemo();
public:
    Demo(char *path);
    void run();
};