#ifndef PAUSE_SCREEN_H
#define PAUSE_SCREEN_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include "Shader.h"

class PauseScreen {
public:
    PauseScreen();
    ~PauseScreen();

    void setup();
    void draw();
    void cleanup();
    void hide();  // Ascunde ecranul de pauză

private:
    GLuint VAO, VBO;
    Shader* shader;  // Use pointer to Shader class
};

#endif // PAUSE_SCREEN_H
