#ifndef PAUSE_SCREEN_H
#define PAUSE_SCREEN_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include "Shader.h"
#include "TextRenderer.h"

class PauseScreen {
public:
    PauseScreen(GLuint width, GLuint height);
    ~PauseScreen();

    void setup();
    void draw();
    void cleanup();

private:
    GLuint VAO, VBO;
    Shader shader;  // Use pointer to Shader class
    GLuint screenWidth, screenHeight;
    TextRenderer* textRenderer;
};

#endif // PAUSE_SCREEN_H
