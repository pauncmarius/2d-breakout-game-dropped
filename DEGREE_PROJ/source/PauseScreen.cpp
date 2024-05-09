#include "PauseScreen.h"
#include "ShaderSources.h"
#define GLT_IMPLEMENTATION
#include "gltext.h"

GLTtext* pauseText;


PauseScreen::PauseScreen() : VAO(0), VBO(0), shader(nullptr) {
}

PauseScreen::~PauseScreen() {
    cleanup();
}

void PauseScreen::setup() {

    shader = new Shader(ShaderSources::vertexShaderSource, ShaderSources::fragmentShaderSource);
    

    float vertices[] = {
        -1.0f, -1.0f,  // Bottom Left
         1.0f, -1.0f,  // Bottom Right
         1.0f,  1.0f,  // Top Right
        -1.0f,  1.0f   // Top Left
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void PauseScreen::draw() {

    shader->use();
    glUniform4f(glGetUniformLocation(shader->ID, "objectColor"), 0.5f, 0.5f, 0.5f, 0.7f);  // Semi-transparent gray

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(0);
    
    glDisable(GL_BLEND);
}

void PauseScreen::cleanup() {
    if (shader) {
        delete shader;
        shader = nullptr;
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}