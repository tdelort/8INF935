cmake_minimum_required(VERSION 3.13)

project(Project)

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(src)
add_subdirectory(libs)
target_link_libraries(${PROJECT_NAME} IMGUI GLAD glm::glm)
include_directories(include)