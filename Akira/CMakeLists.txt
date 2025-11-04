#
# Akira
#

set(SOURCES
vendor/stb/stb_image.h
vendor/stb/stb_image.cpp
Source/Core/Application.h
Source/Core/Application.cpp
Source/Core/Window.h
Source/Core/Window.cpp
Source/Core/Layer.h
Source/Core/Layer.cpp
Source/Core/Logger.h
Source/Core/Logger.cpp
Source/Core/Renderer/Renderer.h
Source/Core/Renderer/Renderer.cpp
Source/Core/Renderer/Shader.h
Source/Core/Renderer/Shader.cpp
Source/Core/Renderer/GLUtils.h
Source/Core/Renderer/GLUtils.cpp
)

add_library(Akira STATIC)

target_sources(Akira PRIVATE ${SOURCES})

# Match VS filters to directory structure on disk
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

add_compile_definitions(
    GLFW_INCLUDE_NONE
)

target_link_libraries(Akira glfw)
target_link_libraries(Akira glad)
target_link_libraries(Akira glm)
target_link_libraries(Akira spdlog)

target_include_directories(Akira PUBLIC "Source" "vendor/stb")
