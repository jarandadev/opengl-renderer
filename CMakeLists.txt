cmake_minimum_required(VERSION 3.16)
project(OpenGLRenderer LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

# Try finding GLFW package
find_package(glfw3 QUIET)

if(NOT glfw3_FOUND)
    FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4
    )
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
    
    FetchContent_MakeAvailable(glfw)
endif()

find_package(OpenGL REQUIRED)

# List source files explicitly
set(SOURCE_FILES
    src/main.cpp
    src/engine/Camera.cpp
    src/engine/Engine.cpp
    src/engine/Input.cpp
    src/engine/ResourceManager.cpp
    src/engine/Time.cpp
    src/engine/Window.cpp
    src/renderer/Material.cpp
    src/renderer/Mesh.cpp
    src/renderer/MeshFactory.cpp
    src/renderer/Renderer.cpp
    src/renderer/Shader.cpp
    src/renderer/Texture.cpp
    src/scene/nodes/LightNode.cpp
    src/scene/nodes/MeshNode.cpp
    src/scene/SceneTree.cpp
)

# External libraries
add_library(glad STATIC third-party/glad/glad.c)
target_include_directories(glad PUBLIC third-party)

add_library(stb STATIC third-party/stb/stb_image.cpp)
target_include_directories(stb PUBLIC third-party)

add_library(glm INTERFACE)
target_include_directories(glm INTERFACE third-party)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Include src directory for header resolution
target_include_directories(${PROJECT_NAME} PRIVATE src)

# Link dependencies
target_link_libraries(${PROJECT_NAME} PRIVATE
    glad
    stb
    glfw
    glm
    OpenGL::GL
)

target_compile_definitions(${PROJECT_NAME} PRIVATE 
    ROOT_DIR="${CMAKE_SOURCE_DIR}/"
)

if(APPLE)
    target_compile_definitions(${PROJECT_NAME} PRIVATE GL_SILENCE_DEPRECATION)
endif()