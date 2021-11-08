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

enum class State {
    SET,
    PLAY
};

namespace Params {
    const float K = 0.5f;
};

inline float frand(int lo, int hi)
{
    return lo + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(hi-lo)));
}

int main()
{
	Gui gui;
    ImVec4 clear_color = ImVec4(0, 0, 0, 1);

    int s = 16;
    std::vector<std::pair<Particle*, Cube>> blob;

    GLuint shader = createProgram();

    for(int i = 0; i < s; i++)
    {
        float pos[3] = {frand(-2, 2), frand(-2, 2), frand(-2, 2)};
        Particle* p = new Particle();
        p->setMass(1.0);
        p->setPosition(Vector3D(pos[0], pos[1], pos[2]));
        
        Cube c(shader);
        c.SetScale(glm::vec3(0.1f));
        c.SetColor(glm::vec3(1.0f));
        c.SetPosition(glm::vec3(pos[0], pos[1], pos[2]));

        blob.push_back(std::pair<Particle*, Cube>(p, c));
    }

    ParticleContactResolver contactsResolver;
    std::vector<ParticleContact*> contacts;
    std::vector<ParticleCable> cables;

    ParticleForceRegistry reg;

    ParticleAnchoredSpring* pas = new ParticleAnchoredSpring(Params::K * 2, 1.0f, Vector3D(0,0,0));
    for(int i = 0; i < s; i++)
    {
        reg.AddEntry(blob[i].first, pas);
        for(int p = 0; p < blob.size(); p++)
        {
            if(p != i)
            {
                reg.AddEntry(blob[i].first, new ParticleSpring(Params::K, 1.0f, blob[p].first));
                ParticleCable c;
                c.maxlength = 1.5f;
                c.restitution = 1.0f;
                c.particle[0] = blob[i].first;
                c.particle[1] = blob[p].first;
                cables.push_back(c);
            }
        }
        //reg.AddEntry(blob.at(i).first, new ParticleGravity(Vector3D(0, -9.81, 0)));
        reg.AddEntry(blob.at(i).first, new ParticleDrag(0.2f, 0.02f));
    }

    Grid grid(Grid::CreateProgram());

    double lastFrameTime = glfwGetTime();

    float px = 0, py = 0, pz = 0;
	while (gui.isOpen())
	{
        gui.pollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        ImGui::NewFrame();
        ImGui::Begin("Config", 0, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("Position");
        ImGui::SliderFloat("Px", &px, -5.0f, 5.0f); ImGui::SameLine();
        ImGui::SliderFloat("Py", &py, -5.0f, 5.0f); ImGui::SameLine();
        ImGui::SliderFloat("Pz", &pz, -5.0f, 5.0f);
        ImGui::End();

        pas->SetAnchor(Vector3D(px,py,pz));

        gui.clear(clear_color);
        glm::mat4 view = glm::lookAt(
            glm::vec3(5.0f, 1.0f, 5.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );

        int width, height;
        glfwGetWindowSize(gui.GetWindow(), &width, &height);
        glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 1.0f, 100.0f);

        double deltaTime = glfwGetTime() - lastFrameTime;
        lastFrameTime = glfwGetTime();

        contacts.clear();
        //std::cout << "avant " << blob[15].first.forces().size() << std::endl;
        reg.UpdateForce(deltaTime);
        //std::cout << "apres " << blob[15].first.forces().size() << std::endl;

        //contacts after forces
        for(auto cable : cables)
        {
            cable.AddContact(&contacts);
        }

        contactsResolver.resolveContacts(&contacts, deltaTime);

        for(int i = 0; i < blob.size(); i++)
            blob[i].first->Integrate(deltaTime);

        for(int i = 0; i < blob.size(); i++)
        {
            Vector3D v = blob[i].first->position();
            blob[i].second.SetPosition(glm::vec3(v.x(), v.y(), v.z()));
            blob[i].second.Draw(proj, view);
        }


        grid.Draw(proj, view);
        gui.swapBuffers();
	}
    
    // destructor of Gui called during this return
    return 0;
}
