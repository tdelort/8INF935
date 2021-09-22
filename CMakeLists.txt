cmake_minimum_required(VERSION 3.10)

project(Demo)

add_library(Vector3D STATIC Vector3D.cpp)
add_library(Particle STATIC Particle.cpp)
add_executable(Demo demo.cpp)
target_link_libraries(Demo Vector3D)
target_link_libraries(Demo Particle)