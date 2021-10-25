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

#include <Gui.h>
#include <Cube.h>
#include <Grid.h>
#include <Particle.h>
#include <Shader.h>

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
    const float K = 1.0f;
};

int main()
{
	Gui gui;
    ImVec4 clear_color = ImVec4(0, 0, 0, 1);

    std::vector<std::pair<Particle, Cube>> blob;

    GLuint shader = createProgram();

    int sx = 4, sz = 4;
    for(int i = 0; i < sx; i++)
    {
        for(int j = 0; j < sz; j++)
        {
            float pos[3] = {i - 2.0, -j + 2.0, 0 };
            Particle p;
            p.setMass(1.0);
            p.setPosition(Vector3D(pos[0], pos[1], pos[2]));
            
            Cube c(shader);
            c.SetScale(glm::vec3(0.1f));
            c.SetColor(glm::vec3(1.0f));
            c.SetPosition(glm::vec3(pos[0], pos[1], pos[2]));

            blob.push_back(std::pair<Particle, Cube>(p, c));
        }
    }

    ParticleForceRegistry reg;

    for(int i = 0; i < sx; i++)
    {
        for(int j = 0; j < sz; j++)
        {   
            std::cout << "i j " << i << " " << j << std::endl;
            bool a = j < sz - 1;
            bool b = i < sx - 1;
            if(a)
            {
                reg.AddEntry(&blob.at(j + i*sx).first, &ParticleSpring(Params::K, 1.0f, &blob.at((j+1) + sx*i).first));
            }

            if(b)
            {
                reg.AddEntry(&blob.at(j + i*sx).first, &ParticleSpring(Params::K, 1.0f, &blob.at(j + sx*(i + 1)).first));
                std::cout << "con : " << (j + i*sx) << " " << (j + sx*(i + 1)) << std::endl;
            }

            if(a && b)
            {
                reg.AddEntry(&blob.at(j + i*sx).first, &ParticleSpring(Params::K, 1.0f, &blob.at((j+1) + sx*(i + 1)).first));
            }

            //reg.AddEntry(&blob.at(j + i*4).first, &ParticleGravity(Vector3D(0, -9.81, 0)));
            //reg.AddEntry(&blob.at(j + i*4).first, &ParticleDrag(0.1f, 0.01f));
        }
    }

    blob[15].second.SetColor(glm::vec3(0,1,1));

    std::cout << blob.size() << std::endl;

    Grid grid(Grid::CreateProgram());

    double lastFrameTime = glfwGetTime();

	while (gui.isOpen())
	{
        gui.pollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


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

        for(int i = 0; i < blob.size(); i++)
            blob[i].first.clearForces();

        std::cout << "avant " << blob[15].first.forces().size() << std::endl;
        reg.UpdateForce(deltaTime);
        std::cout << "apres " << blob[15].first.forces().size() << std::endl;

        for(int i = 0; i < blob.size(); i++)
            blob[i].first.Integrate(deltaTime);

        for(int i = 0; i < blob.size(); i++)
        {
            Vector3D v = blob[i].first.position();
            blob[i].second.SetPosition(glm::vec3(v.x(), v.y(), v.z()));
            blob[i].second.Draw(proj, view);
        }


        grid.Draw(proj, view);
        gui.swapBuffers();
	}
    
    // destructor of Gui called during this return
    return 0;
}
