cmake_minimum_required(VERSION 3.23)
project(scape)
set(CMAKE_CXX_STANDARD 17)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only")
set(GLFW_INSTALL OFF CACHE BOOL "GLFW lib only")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "GLFW lib only")

find_package(OpenGL REQUIRED)

add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glad)
add_subdirectory(vendor/imgui)

add_executable(scape src/main.cpp)
target_link_libraries(${PROJECT_NAME} glfw glad ImGui)
target_link_libraries(ImGui glfw)
target_include_directories(${PROJECT_NAME} PUBLIC
        ${OpenGL_INCLUDE_DIRS}
        vendor/glfw/include
        vendor/imgui
        vendor/imgui/backends
)
