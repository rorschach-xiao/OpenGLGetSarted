#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


#include <common/Model.h>
#include <common/camera.h>
#include <common/Light.h>
#include <common/Skybox.h>
#include <common/Text.h>


using namespace common;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
unsigned int loadTexture(const char *path);

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = 800.0f / 2.0f;
float lastY = 600.0f / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;
float lastTime = 0.0f;
int frameCount = 0;
float fps = 0.0f;

// lighting
Light lightManager = Light(1.0f, 0.01f, 0.005f);
glm::vec3 lightPos(-1.5f, 5.5f, 2.5f);
float totalRotation = 0.0f;


int main(int argc, const char * argv[]) {
    GLFWwindow* win;
    if(!glfwInit()) {
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    win = glfwCreateWindow(800, 600, "Demo", NULL, NULL);
    if(!win) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(win);
    int bufferWidth;
    int bufferHeight;
    glfwGetFramebufferSize(win, &bufferWidth, &bufferHeight);
    glfwMakeContextCurrent(win);
    glfwSetFramebufferSizeCallback(win, framebuffer_size_callback);
    glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(win, mouse_callback);
    glfwSetScrollCallback(win, scroll_callback);

    // gl function initialization
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD.\n";
        glfwTerminate();
        return -1;
    }
    glViewport(0, 0, bufferWidth, bufferHeight);

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

//    // Set OpenGL options
//    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Compile and setup the font shader
    MyShaderProgram fontShader;
    if (!fontShader.LoadShader("../shaders/text.vert", "../shaders/text.frag")) {
        std::cout << "Failed load text shader.\n";
        glfwTerminate();
        return -1;
    }

    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(800.0f), 0.0f, static_cast<GLfloat>(600.0f));
    fontShader.UseProgram();
    glUniformMatrix4fv(glGetUniformLocation(fontShader.GetShaderId(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    // init Text render
    Text textRender = Text("../font/Antonio-Bold.ttf");

    // build and compile shaders
    MyShaderProgram myShader;
    if (!myShader.LoadShader("../shaders/lightVertex.vert", "../shaders/lightFrag.frag")) {
        std::cout << "Failed load simple light shader.\n";
        glfwTerminate();
        return -1;
    }

    MyShaderProgram reflectShader;
    if (!reflectShader.LoadShader("../shaders/reflectVertex.vert", "../shaders/reflectFrag.frag")) {
        std::cout << "Failed load simple reflect shader.\n";
        glfwTerminate();
        return -1;
    }

    MyShaderProgram lampShader;
    if (!lampShader.LoadShader("../shaders/lightVertex.vert", "../shaders/lampFrag.frag")) {
        std::cout << "Failed load simple lamp shader.\n";
        glfwTerminate();
        return -1;
    }

    MyShaderProgram skyboxShader;
    if (!skyboxShader.LoadShader("../shaders/skyboxVertex.vert", "../shaders/skyboxFrag.frag")) {
        std::cout << "Failed load simple skybox shader.\n";
        glfwTerminate();
        return -1;
    }


    // load models
    // -----------
    Model myModel("../assets/models/nanosuit/nanosuit.obj");

    // load skybox
    // -----------
    Skybox skybox = Skybox("../assets/models/skybox");
    skyboxShader.UseProgram();
    skyboxShader.SetInt("skybox", 0);

    reflectShader.UseProgram();
    reflectShader.SetInt("skybox", 0);

    // add light
    // -----------
    myShader.UseProgram();

    // add lights
    // ----------
    lightManager.AddDirectionLight(myShader,
                                   glm::vec3(-1.0f, 2.0f, -0.3f),
                                   glm::vec3(0.05f, 0.05f,0.05f),
                                   glm::vec3(0.4f, 0.4f, 0.4f),
                                   glm::vec3(0.5f, 0.5f, 0.5f));



    // render loop
    while (!glfwWindowShouldClose(win))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        frameCount++;
        if (currentFrame - lastTime >= 1.0) { // 如果超过1秒
            fps = frameCount / (currentFrame - lastTime);
            cout << "FPS: " << fps << endl;
            frameCount = 0;
            lastTime += 1;
        }
        totalRotation += deltaTime * 0.001f;


        // input
        // -----
        processInput(win);

        // render
        // ------
        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        textRender.RenderText(fontShader, "FPS: " + to_string(int(fps)), 700.0f, 570.0f, 0.5f, glm::vec3(0.2, 0.2f, 0.2f));

        // don't forget to enable shader before setting uniforms
        myShader.UseProgram();
        glm::mat4 trans = glm::mat4(1.0);
        trans = glm::rotate(trans, totalRotation, glm::normalize(glm::vec3(1.0f, 1.0f, 0.0f)));
        glm::vec4 lightPos_aug = glm::vec4(lightPos, 1.0);
        lightPos_aug = trans * lightPos_aug;

        lightPos = glm::vec3(lightPos_aug[0], lightPos_aug[1], lightPos_aug[2]);
        lightManager.AddPointLight(myShader,
                                   lightPos,
                                   glm::vec3 (0.05f, 0.05f, 0.05f),
                                   glm::vec3 (0.8f, 0.8f, 0.8f),
                                   glm::vec3 (1.0f, 1.0f, 1.0f));

        lightManager.AddSpotLight(myShader, camera.Position,camera.Front,
                                  glm::vec3 (0.0f, 0.0f, 0.0f),
                                  glm::vec3 (1.0f, 1.0f, 1.0f),
                                  glm::vec3 (1.0f, 1.0f, 1.0f), 12.5f, 17.5f);


        myShader.SetVec3("viewPos", camera.Position);

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        myShader.SetMat4("projection", projection);
        myShader.SetMat4("view", view);

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
        myShader.SetMat4("model", model);
        myModel.Draw(myShader);

        // render reflected-version loaded model
        reflectShader.UseProgram();
        reflectShader.SetMat4("projection", projection);
        reflectShader.SetMat4("view", view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 5.0f)); // translate it down so it's at the center of the scene
        model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
        reflectShader.SetMat4("model", model);
        myModel.Draw(reflectShader);


        // render lamp
        lampShader.UseProgram();
        lampShader.SetMat4("projection", projection);
        lampShader.SetMat4("view", view);
        lightManager.AddLamp(lampShader, lightPos);

        // draw skybox at last
        glDepthFunc(GL_LEQUAL);
        skyboxShader.UseProgram();
        view = glm::mat4(glm::mat3(camera.GetViewMatrix())); // remove translation from the view matrix
        skyboxShader.SetMat4("view", view);
        skyboxShader.SetMat4("projection", projection);
        skybox.Render(skyboxShader);
        glDepthFunc(GL_LESS);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(win);
        glfwPollEvents();
    }


    glfwTerminate();
    exit(EXIT_SUCCESS);
    return 0;
}

//// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
//// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) { glfwSetWindowShouldClose(window, true); }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if(firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

//
//// glfw: whenever the window size changed (by OS or user resize) this callback function executes
//// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const * path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}