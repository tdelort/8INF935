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

#include <vector>

class Demo
{
    enum class DemoState {
        MENU,
        SPHERE_SPHERE,
        BOX_PLANE,
        OCTREE
    };

    bool running;
    bool showOctree;
    std::vector<GameObject*> objects;

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

    void ClearObjects();
    GameObject* CreateObject(const Vector3D& position, Primitive::Type type);
    void Draw();

    void OnCollision(Contact* data);
    std::vector<Contact*> lastContacts;
public:
    Demo();
    void run();
};