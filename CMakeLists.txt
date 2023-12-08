
cmake_minimum_required(VERSION 3.21)
project(OpenGLGetStarted)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_OSX_ARCHITECTURES  "arm64" CACHE STRING "Build architectures for Mac OS X" FORCE)

set(LOCAL_H /opt/homebrew/include)
include_directories(${LOCAL_H})
set(GLOBAL_H /usr/local/include)
include_directories(${GLOBAL_H})
set(PROJ_H ./include)
include_directories(${PROJ_H})
set(FREETYPE_H /opt/homebrew/Cellar/freetype/2.13.2/include/freetype2)
include_directories(${FREETYPE_H})

set(GLEW_H /opt/homebrew/Cellar/glew/2.2.0_1/include/GL)
set(GLFW_H /opt/homebrew/Cellar/glfw/3.3.8/include/GLFW)
set(GLM_H /opt/homebrew/Cellar/glm/0.9.9.8/include/glm)
link_directories(${GLEW_H} ${GLFW_H} ${GLM_H})

set(GLEW_LINK /opt/homebrew/Cellar/glew/2.2.0_1/lib/libGLEW.2.2.dylib)
set(GLFW_LINK /opt/homebrew/Cellar/glfw/3.3.8/lib/libglfw.3.dylib)
set(ASSIMP_LINK /opt/homebrew/Cellar/assimp/5.3.1/lib/libassimp.5.dylib)
set(FREETYPE_LINK /opt/homebrew/Cellar/freetype/2.13.2/lib/libfreetype.6.dylib)
link_libraries(${OPENGL} ${GLEW_LINK} ${GLFW_LINK} ${ASSIMP_LINK} ${FREETYPE_LINK})

add_executable(OpenGL src/glad/glad.c src/Main.cpp
        src/common/MyShaderProgram.cpp src/common/stb_image.cpp
        src/common/Mesh.cpp
        src/common/Model.cpp
        src/common/Light.cpp
#        include/common/Light.h
#        include/common/Skybox.h
        src/common/Skybox.cpp
        src/common/Text.cpp
#        include/common/Text.h
)

if (APPLE)
    target_link_libraries(OpenGL "-framework OpenGL")
    target_link_libraries(OpenGL "-framework GLUT")
endif ()