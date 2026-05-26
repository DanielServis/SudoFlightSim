#include <iostream>
#include <GLFW/glfw3.h>

#include "Input.h"

bool Input::keys[1024] = {false};
bool Input::mouseButtons[8] = {false};

void Input::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
        keys[key] = true;
    if (action == GLFW_RELEASE)
        keys[key] = false;
}

void Input::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
    if (action == GLFW_PRESS)
        mouseButtons[button] = true;
    if (action == GLFW_RELEASE)
        mouseButtons[button] = false;
}

bool Input::getKeyDown(int key)
{
    return keys[key];
}

bool Input::getMouseButtonDown(int button)
{
    return mouseButtons[button];
}