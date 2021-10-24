target_sources(${PROJECT_NAME}
	PRIVATE
		Vector3D.cpp
		Particle.cpp
		Gui.cpp
		IDrawable.cpp
		Cube.cpp
		Camera.cpp
		Grid.cpp
)

add_subdirectory(particle_forces)
#add_subdirectory(particle_contacts)
