#pragma once
#include <GLFW/glfw3.h>

#ifndef INPUT_H
    #define INPUT_H

    class Input
    {
        private:
            static bool keys[1024];
            static bool mouseButtons[8];

            Input() = delete;

        public:
            static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
            static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
            static bool getKeyDown(int key);
            static bool getMouseButtonDown(int button);
    };
    
#endif