#include <common/Light.h>
#include <common/Mesh.h>

using namespace std;

namespace common {
    Light::Light(float attenuationConstant, float attenuationLinear, float attenuationQuadratic) {
        this->constant = attenuationConstant;
        this->linear = attenuationLinear;
        this->quadratic = attenuationQuadratic;
    }

    void Light::AddDirectionLight(MyShaderProgram shader, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse,
                                  glm::vec3 speclar) {
        shader.UseProgram();
        shader.SetVec3("dirLight.ambient",  ambient);
        shader.SetVec3("dirLight.diffuse", diffuse);
        shader.SetVec3("dirLight.specular", speclar);
        shader.SetVec3("dirLight.direction",  direction);
    }

    void Light::AddPointLight(common::MyShaderProgram shader, glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse,
                              glm::vec3 speclar) {
        // config light
        shader.UseProgram();
        shader.SetVec3("pointLight.ambient",  ambient);
        shader.SetVec3("pointLight.diffuse", diffuse);
        shader.SetVec3("pointLight.specular", speclar);
        shader.SetVec3("pointLight.position", position);
        shader.SetFloat("pointLight.constant", constant);
        shader.SetFloat("pointLight.linear", linear);
        shader.SetFloat("pointLight.quadratic", quadratic);
    }

    void Light::AddSpotLight(common::MyShaderProgram shader, glm::vec3 position, glm::vec3 direction, glm::vec3 ambient,
                             glm::vec3 diffuse, glm::vec3 speclar, float cutOff, float outerCutOff) {
        shader.UseProgram();
        shader.SetVec3("spotLight.ambient",  ambient);
        shader.SetVec3("spotLight.diffuse", diffuse);
        shader.SetVec3("spotLight.specular", speclar);
        shader.SetVec3("spotLight.position", position);
        shader.SetVec3("spotLight.direction", direction);
        shader.SetFloat("spotLight.cutOff",   glm::cos(glm::radians(cutOff)));
        shader.SetFloat("spotLight.outerCutOff",   glm::cos(glm::radians(outerCutOff)));
        shader.SetFloat("spotLight.constant", constant);
        shader.SetFloat("spotLight.linear", linear);
        shader.SetFloat("spotLight.quadratic", quadratic);
    }

    void Light::AddLamp(common::MyShaderProgram shader, glm::vec3 position) {
        // config lamp
        float vertices[] = {
                // positions          // normals           // texture coords
                -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
                0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
                0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
                0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
                -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

                -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
                0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
                0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
                0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
                -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
                -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

                -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
                -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
                -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
                -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
                -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
                -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

                0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
                0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
                0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
                0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
                0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
                0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

                -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
                0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
                0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
                0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

                -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
                0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
                0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
                0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
                -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
                -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
        };
        std::vector<Vertex> vertexVector;
        vertexVector.reserve(36);

        for (int i = 0; i < 36; ++i) {
            Vertex vertex;
            vertex.Position = glm::vec3(vertices[i * 8], vertices[i * 8 + 1], vertices[i * 8 + 2]);
            vertex.Normal = glm::vec3(vertices[i * 8 + 3], vertices[i * 8 + 4], vertices[i * 8 + 5]);
            vertex.TexCoords = glm::vec2(vertices[i * 8 + 6], vertices[i * 8 + 7]);
            vertexVector.push_back(vertex);
        }
        unsigned int indices[] = {
                0, 1, 2,   // 第一个三角形
                3, 4, 5,   // 第二个三角形
                6, 7, 8,   // 第三个三角形
                9, 10, 11, // 第四个三角形
                12, 13, 14, // 第五个三角形
                15, 16, 17, // 第六个三角形
                18, 19, 20, // 第七个三角形
                21, 22, 23, // 第八个三角形
                24, 25, 26, // 第九个三角形
                27, 28, 29, // 第十个三角形
                30, 31, 32, // 第十一个三角形
                33, 34, 35  // 第十二个三角形
        };
        shader.UseProgram();
        vector<unsigned int> indicesVector(indices, indices + 36);
        vector<Texture> texture = {};
        Mesh lamp = Mesh(vertexVector, indicesVector, texture);
        // translate the lamp to the light position
        glm::mat4 model = glm::mat4(1.0f);
        //model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
        model = glm::translate(model, position);

        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
        shader.SetMat4("model", model);
        lamp.Draw(shader);
    }

}