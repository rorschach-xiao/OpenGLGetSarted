#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <string>
#include <vector>
#include "MyShaderProgram.h"

#ifndef GETSTARTED_LIGHT_CPP_H
#define GETSTARTED_LIGHT_CPP_H

struct DirectionLight {
    glm::vec3 Direction;
    glm::vec3 Ambient;
    glm::vec3 Diffuse;
    glm::vec3 Specular;
};

struct PointLight {
    glm::vec3 Position;
    glm::vec3 Ambient;
    glm::vec3 Diffuse;
    glm::vec3 Specular;

    // attenuation terms
    float Constant;
    float Linear;
    float Quadratic;
};

struct SpotLight {
    glm::vec3  Position;
    glm::vec3  Direction;
    float CutOff;
    float OuterCutOff;
    glm::vec3 Ambient;
    glm::vec3 Diffuse;
    glm::vec3 Specular;

    // attenuation terms
    float Constant;
    float Linear;
    float Quadratic;
};
namespace common {
    class Light {
    public:
        Light(float attenuationConstant, float attenuationLinear, float attenuationQuadratic);
        void AddDirectionLight(MyShaderProgram shader, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 speclar);
        void AddPointLight(MyShaderProgram shader, glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 speclar);
        void AddSpotLight(MyShaderProgram shader, glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 speclar, float cutOff, float outerCutOff);
        void AddLamp(MyShaderProgram shader, glm::vec3 position);
    private:
        // attenuation terms
        float constant;
        float linear;
        float quadratic;
    };

}

#endif //GETSTARTED_LIGHT_CPP_H
