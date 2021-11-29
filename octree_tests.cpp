#define GLFW_INCLUDE_NONE

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
#include <algorithm>

// Physics Engine
#include <Gui.h>
#include <Grid.h>
#include <Cube.h>
#include <Shader.h>
#include <PhysicsEngine.h>
#include <Camera.h>
#include <colliders/Box.h>
#include <OcTree.h>
#include <colliders/Primitive.h>

inline float frand(float lo, float hi)
{
    return lo + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(hi-lo)));
}
#define N 100
int main()
{
    srand(time(NULL));
    Gui* gui = new Gui();
    Grid grid(Grid::CreateProgram());
    ImVec4 clear_color = ImVec4(0, 0, 0, 1);

    OcTree octree(Vector3D(0, 0, 0), Vector3D(10, 10, 10));

    Box* boxes[N];
    Cube* cubes[N];
    for(int i = 0; i < N; i++)
    {
        Vector3D c;
        if (i < N / 4)
            c = Vector3D(frand(0, 2), frand(0, 2), frand(0, 2));
        else if (i < N / 2)
            c = Vector3D(frand(-4, 4), frand(-4, 0), frand(-4, 4));
        else 
            c = Vector3D(frand(-4, 4), frand(-4, 4), frand(-4, 4));
        boxes[i] = new Box();
        boxes[i]->center = c;
        boxes[i]->halfSize = Vector3D(frand(0.1, 0.5), frand(0.1, 0.5), frand(0.1, 0.5)) / 2;
        octree.Insert(boxes[i]);
        cubes[i] = new Cube(createProgram(false));
    }

    std::vector<Primitive*> primitives = octree.Query(boxes[0]);

    for(int i = 0; i < N; i++)
    {
        auto it = std::find(primitives.begin(), primitives.end(), boxes[i]);
        if (it != primitives.end())
            cubes[i]->SetColor(glm::vec3(1, 0, 0));
    }

    cubes[0]->SetColor(glm::vec3(1, 1, 0));

    float startTime = glfwGetTime();
    float theta = 0;
    float radius = 15;
    bool showBoxes = true;
    bool showOctree = true;
    bool showAll = true;
	while(gui->isOpen())
    {
        gui->pollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        ImGui::NewFrame();
        ImGui::Begin("Main Menu", 0, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::SliderFloat("Theta", &theta, 0, 360);
        ImGui::SliderFloat("Radius", &radius, 0, 30);
        ImGui::Checkbox("Show Boxes", &showBoxes);
        ImGui::Checkbox("Show Octree", &showOctree);
        ImGui::Checkbox("Show All", &showAll);
        ImGui::End();

        //theta = (glfwGetTime() - startTime) * 30;
        float rad = theta / 180 * 2 * 3.24;
        gui->clear(clear_color);
        Camera::setView(glm::lookAt(
            glm::vec3(radius * cos(rad), 2, radius * sin(rad)),
            glm::vec3(0, 0, 0),
            glm::vec3(0.0f, 1.0f, 0.0f)
        ));

        int width, height;
        glfwGetWindowSize(gui->GetWindow(), &width, &height);
        Camera::setProj(glm::perspective(glm::radians(45.0f), (float)width / (float)height, 1.0f, 100.0f));

        if(showBoxes)
        {
            for(int i = 0; i < N; i++)
            {
                auto it = std::find(primitives.begin(), primitives.end(), boxes[i]);
                if (showAll || it != primitives.end())
                {
                    cubes[i]->SetPosition(boxes[i]->center);
                    cubes[i]->SetScale(boxes[i]->halfSize * 2);
                    cubes[i]->Draw();
                }
            }
        }
        if (showOctree)
            octree.Draw();
        grid.Draw();

        gui->swapBuffers();
    }

    for(int i = 0; i < N; i++)
    {
        delete cubes[i];
        delete boxes[i];
    }
    delete gui;

    return 0;
}