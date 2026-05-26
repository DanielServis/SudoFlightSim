#include <iostream>
using namespace std;
#include <cstdlib>
#include <unistd.h>
#include <cmath>
#include <ctime>
#include <cstring>
#include <fstream>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GLT_IMPLEMENTATION
#include "gltext.h"

#include "Input.h"
#include "aircraft/AirbusA320neo.h"
#include "misc/Airports.h"

float deltaTime = 0;
float lastTime = 0.0f;
int frameCount = 0;
int fps = 0;

void crash()
{
    cout <<"CRASHED\n\n";
    glfwTerminate();
    _exit(-1);
}

std::string load_file(const std::string& path)
{
    std::ifstream file(path);
    return std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
}

void displayFPS(GLTtext* text, double& prevTime)
{
    float currentTime = glfwGetTime();
    deltaTime = currentTime - lastTime;
    lastTime = currentTime;

    frameCount++;
    if (currentTime - prevTime >= 1.0)
    {
        fps = frameCount;
        frameCount = 0;
        prevTime = currentTime;
    }

    char fpsText[32];
    snprintf(fpsText, sizeof(fpsText), "FPS: %d", fps);
    gltSetText(text, fpsText);

    gltBeginDraw();
    gltColor(1.0f, 1.0f, 1.0f, 1.0f);
    gltDrawText2D(text, 10.0f, 10.0f, 1.5f);
    gltEndDraw();
}

int main()
{
    cout <<"\n";
    srand(time(NULL));

    if (!glfwInit())
    {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *mode = glfwGetVideoMode(monitor);

    GLFWwindow *window = glfwCreateWindow(mode->width, mode->height, "SFsim", monitor, nullptr);
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, Input::keyCallback);
    glfwSetMouseButtonCallback(window, Input::mouseButtonCallback);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        return -1;
    }

    if (!gltInit())
    {
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    std::string vertexShaderSource = load_file("shaders/vertexShader.glsl");
    std::string fragmentShaderSource = load_file("shaders/fragmentShader.glsl");
    if (vertexShaderSource.empty() || fragmentShaderSource.empty())
        return -1;

    const char *vertSrc = vertexShaderSource.c_str();
    const char *fragSrc = fragmentShaderSource.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertSrc, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[1000];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 1000, NULL, infoLog);
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragSrc, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 1000, NULL, infoLog);
    }

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 1000, NULL, infoLog);
        printf("Linking Error : %s\n", infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
    unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
    unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
    unsigned int objectTypeLoc = glGetUniformLocation(shaderProgram, "ID");

    GLTtext *text1 = gltCreateText();
    double prevTime = glfwGetTime();

    AirbusA320neo* plane = new AirbusA320neo(0, 0, -5, 0, 0, 0);
    Runway* runway = new Runway(0, 0, -900, 0, 0, 0);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        displayFPS(text1, prevTime);

        glUseProgram(shaderProgram);

        float view[16] = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, -10, -50, 1
        };

        float fov = 45.0f * 3.14159f / 180.0f;
        float aspect = 1600.0f / 600.0f;
        float near = 0.1f;
        float far = 100000.0f;
        float f = 1.0f / tanf(fov / 2.0f);

        float projection[16] = {
            f / aspect, 0, 0, 0,
            0, f, 0, 0,
            0, 0, (far + near) / (near - far), -1,
            0, 0, (2 * far * near) / (near - far), 0
        };

        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view);
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, projection);

        plane->draw(modelLoc, objectTypeLoc);
        runway->draw(modelLoc, objectTypeLoc);

        glfwSwapBuffers(window);
        glfwPollEvents();

        if (Input::getKeyDown(GLFW_KEY_ESCAPE))
        {
            crash();
        }
    }

    gltTerminate();
    glfwTerminate();
    return 0;
}