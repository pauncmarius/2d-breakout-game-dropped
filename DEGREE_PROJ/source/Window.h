#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include <iostream>
#include <glad/glad.h>

class Window {
public:
    GLFWwindow* window;

    Window(int width, int height, const char* title);
    ~Window();

    bool shouldClose() const;
    void swapBuffersAndPollEvents();
};

#endif // WINDOW_H
