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
        SPHERE_SPHERE,
        BOX_PLANE
    };

    struct {
        GameObject* obj1;
        GameObject* obj2;
        bool running;
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

    void CameraControls();
    void ImguiMenu();
    void ImguiDemo();

    void ClearContext();
    GameObject* CreateObject(const Vector3D& position, Primitive::Type type);
    void Draw();

    void OnCollision(Contact* data);
    Contact* lastContact = nullptr;
public:
    Demo();
    void run();
};