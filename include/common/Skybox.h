#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include "MyShaderProgram.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <vector>

#ifndef GETSTARTED_SKYBOX_H
#define GETSTARTED_SKYBOX_H

namespace common {
    class Skybox {
    public:
        Skybox(std::string skyboxPath);
        void Render(MyShaderProgram skyboxShader);
    private:
        unsigned int skyboxVAO, skyboxVBO;
        std::vector<std::string> faces;
        std::string directory;
        std::vector<float> skyboxVertices;
        unsigned int cubemapTexture;
        void setupSkyBox();
        void loadCubemap();
    };
}
#endif //GETSTARTED_SKYBOX_H
