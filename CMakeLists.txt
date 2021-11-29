cmake_minimum_required(VERSION 3.13)

set(CMAKE_EXPORT_COMPILE_COMMANDS)

project(PhysicsEngine)

add_library(${PROJECT_NAME} STATIC)

add_subdirectory(src)
add_subdirectory(libs)
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} IMGUI GLAD glm::glm)

add_executable(${PROJECT_NAME}Tests octree_tests.cpp)
#add_executable(${PROJECT_NAME}Tests main.cpp demo.cpp)
target_link_libraries(${PROJECT_NAME}Tests ${PROJECT_NAME})