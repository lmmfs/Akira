#
# Akira
#

set(SOURCES
vendor/stb/stb_image.h
vendor/stb/stb_image.cpp
Source/Akira/Application.h
Source/Akira/Application.cpp
Source/Akira/Window.h
Source/Akira/Window.cpp
Source/Akira/Layer.h
Source/Akira/Layer.cpp
Source/Akira/Logger.h
Source/Akira/Logger.cpp
Source/Akira/Events/Event.h
Source/Akira/Events/ApplicationEvent.h
Source/Akira/Events/KeyEvent.h
Source/Akira/Events/MouseEvent.h
Source/Akira/Renderer/Renderer.h
Source/Akira/Renderer/Renderer.cpp
Source/Akira/Renderer/Shader.h
Source/Akira/Renderer/Shader.cpp
Source/Akira/Renderer/GLUtils.h
Source/Akira/Renderer/GLUtils.cpp
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
