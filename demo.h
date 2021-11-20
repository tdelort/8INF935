#pragma once

#define GLFW_INCLUDE_NONE

#include <Gui.h>
#include <Cube.h>
#include <ObjMesh.h>
#include <Grid.h>

class Demo
{
    enum class DemoState {
        MENU,
        SAMPLE_DEMO,
        COLLISION_DEMO
    };

    DemoState demoState = DemoState::MENU;

    ImVec4 clear_color;

    char* meshPath;

    float r;

    void ImguiMenu();
    void ImguiSampleDemo();
    void ImguiCollisionDemo();
public:
    Demo(char *path);
    void run();
};