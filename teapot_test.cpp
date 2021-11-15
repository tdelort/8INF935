#define GLFW_INCLUDE_NONE

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glad/glad.h>

#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include <iostream>
#include <cstdlib>

#include <Gui.h>
#include <Cube.h>
#include <ObjMesh.h>
#include <Grid.h>
#include <Particle.h>
#include <Shader.h>
#include <Matrix.h>

#include <particle_forces/ParticleSpring.h>
#include <particle_forces/ParticleAnchoredSpring.h>
#include <particle_forces/ParticleGravity.h>
#include <particle_forces/ParticleDrag.h>
#include <particle_forces/ParticleForceRegistry.h>

#include <particle_contacts/ParticleContact.h>
#include <particle_contacts/ParticleRod.h>
#include <particle_contacts/ParticleCable.h>
#include <particle_contacts/ParticleContactResolver.h>

int main()
{
	Gui gui;
    ImVec4 clear_color = ImVec4(0, 0, 0, 1);

    GLuint shader = createProgram();
        
    ObjMesh c(shader, "D:\\0 - Code\\UQAC\\8INF935 - Math et Physique pour Info\\Projet\\teapot.obj");
    c.SetScale(glm::vec3(0.3f));
    c.SetColor(glm::vec3(1.0f));
    c.SetPosition(glm::vec3(0, 0, 0));
    c.SetRotation(glm::vec3(0.0f, 30.0f, 0.0f));

    Grid grid(Grid::CreateProgram());

    float rx = 0, ry = 0, rz = 0;
	while (gui.isOpen())
	{
        gui.pollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        ImGui::NewFrame();
        ImGui::Begin("Config", 0, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::SliderFloat("Rx", &rx, -3.14f, 3.14f); ImGui::SameLine();
        ImGui::SliderFloat("Ry", &ry, -3.14f, 3.14f); ImGui::SameLine();
        ImGui::SliderFloat("Rz", &rz, -3.14f, 3.14f);
        ImGui::End();

        gui.clear(clear_color);
        glm::mat4 view = glm::lookAt(
            glm::vec3(5.0f, 1.0f, 5.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );

        int width, height;
        glfwGetWindowSize(gui.GetWindow(), &width, &height);
        glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 1.0f, 100.0f);

        c.SetRotation(glm::vec3(rx, ry, rz));

        c.Draw(proj, view);
        grid.Draw(proj, view);
        gui.swapBuffers();
	}
    
    // destructor of Gui called during this return
    return 0;
}
