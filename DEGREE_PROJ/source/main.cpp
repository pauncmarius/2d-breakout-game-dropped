//main.cpp
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Rectangle.h"
#include <vector>
#include "ShaderSources.h"
#include "Circle.h"
#include "PauseScreen.h"
#include "TextRenderer.h"

// Constante pentru dimensiuni și culori
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const glm::vec4 BACKGROUND_COLOR(0.2f, 0.3f, 0.3f, 1.0f);
const glm::vec4 DRAWING_AREA_COLOR(0.1f, 0.1f, 0.1f, 1.0f);
bool isPaused = false;

std::vector<std::vector<int>> matrix = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS && isPaused) {
        isPaused = false;  // Resume the game when space is pressed    
    }
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    isPaused = true;
}

void setupViewport(int width, int height) {
    int viewportSize = std::min(width, height);
    int xOffset = (width - viewportSize) / 2;
    int yOffset = (height - viewportSize) / 2;
    glViewport(xOffset, yOffset, viewportSize, viewportSize);
    glScissor(xOffset, yOffset, viewportSize, viewportSize);
}

void initializeGLFW() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLFWwindow* createWindow(int width, int height) {
    GLFWwindow* window = glfwCreateWindow(width, height, "Test", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window.\n";
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    return window;
}

int main() {

    initializeGLFW();
    GLFWwindow* window = createWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD.\n";
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    std::cout << "Initializing shaderProgram...\n";
    Shader shaderProgram(ShaderSources::vertexShaderSource, ShaderSources::fragmentShaderSource);
    shaderProgram.use();

    PauseScreen pauseScreen(WINDOW_WIDTH, WINDOW_HEIGHT);
    pauseScreen.setup();

    // Obține locațiile uniformelor din shader
    unsigned int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
    unsigned int colorLoc = glGetUniformLocation(shaderProgram.ID, "objectColor");
    unsigned int translationLoc = glGetUniformLocation(shaderProgram.ID, "translation");

    Rectangle rectangle(1.0f, 1.0f);
    Circle circle(0.04f, 36, glm::vec3(0.5f, 0.5f, 0.0f));  // inițializează cu o culoare gri

    float lastTime = glfwGetTime();
    // Loop-ul de redare
    while (!glfwWindowShouldClose(window)) {
        int width, height;
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        glClearColor(BACKGROUND_COLOR.r, BACKGROUND_COLOR.g, BACKGROUND_COLOR.b, BACKGROUND_COLOR.a);
        glClear(GL_COLOR_BUFFER_BIT);

        int viewportSize = std::min(width, height);
        int xOffset = (width - viewportSize) / 2;
        int yOffset = (height - viewportSize) / 2;

        glEnable(GL_SCISSOR_TEST);
        glScissor(xOffset, yOffset, viewportSize, viewportSize);
        glClearColor(DRAWING_AREA_COLOR.r, DRAWING_AREA_COLOR.g, DRAWING_AREA_COLOR.b, DRAWING_AREA_COLOR.a);
        glClear(GL_COLOR_BUFFER_BIT);
        glDisable(GL_SCISSOR_TEST);

        setupViewport(width, height);

        //blocuri
        float cellWidth = static_cast<float>(std::min(width, height)) / matrix[0].size();
        float cellHeight = static_cast<float>(std::min(width, height)) / matrix.size();
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix[0].size(); ++j) {
                if (matrix[i][j] == 1) {
                    glm::mat4 model = glm::mat4(1.0f);
                    model = glm::translate(model, glm::vec3(
                        -1.0f + 2.0f * (j) / matrix[0].size(),  // Centrarea fiecărui dreptunghi
                        1.0f - 2.0f * (i + 1.0f) / matrix.size(),  // in mijlocul celulei sale
                        0.0f
                    ));
                    model = glm::scale(model, glm::vec3(
                        2.0f / matrix[0].size(),   // Scalați pentru a umple celula
                        2.0f / matrix.size(),   // fără a depăși
                        1.0f
                    ));

                    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
                    glm::vec4 rectangleColor(1.0f, 1.0f, 0.0f, 1.0f); // galben
                    unsigned int colorLoc = glGetUniformLocation(shaderProgram.ID, "objectColor");
                    glUniform4f(colorLoc, rectangleColor.r, rectangleColor.g, rectangleColor.b, rectangleColor.a);
                    rectangle.draw();
                }
            }
        }
        //minge
        glm::vec3 circlePosition = glm::vec3(0.0f, -0.9f, 0.0f);  // Poziția centrală
        glm::vec4 circleColor = glm::vec4(0.6f, 0.6f, 0.6f, 1.0f);  // Culoare vizibilă
        unsigned int colorLoc = glGetUniformLocation(shaderProgram.ID, "objectColor");
		glUniform4f(colorLoc, circleColor.r, circleColor.g, circleColor.b, circleColor.a);
        glUniform3fv(translationLoc, 1, glm::value_ptr(circlePosition));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));  // Matricea de model la identitate

        circle.update(deltaTime, isPaused);
        circle.draw();  // Desenează cercul

        if (isPaused) {

            pauseScreen.draw();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}