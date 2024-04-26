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

// Constante pentru dimensiuni și culori
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const glm::vec4 BACKGROUND_COLOR(0.2f, 0.3f, 0.3f, 1.0f);
const glm::vec4 DRAWING_AREA_COLOR(0.1f, 0.1f, 0.1f, 1.0f);

std::vector<std::vector<int>> matrix = {
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
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

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD.\n";
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // Configurarea shader-ului și a dreptunghiurilor
    Shader shaderProgram(ShaderSources::vertexShaderSource, ShaderSources::fragmentShaderSource);
    shaderProgram.use();

    unsigned int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
    Rectangle rectangle(1.0f, 1.0f);
    Circle circle(0.04f, 36);

    // Loop-ul de redare
    while (!glfwWindowShouldClose(window)) {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        glClearColor(BACKGROUND_COLOR.r, BACKGROUND_COLOR.g, BACKGROUND_COLOR.b, BACKGROUND_COLOR.a);
        glClear(GL_COLOR_BUFFER_BIT);

        // Calculate minimum dimension to maintain a square viewport
        int viewportSize = std::min(width, height);
        int xOffset = (width - viewportSize) / 2;
        int yOffset = (height - viewportSize) / 2;

        // Enable scissor test to clear only the drawing area
        glEnable(GL_SCISSOR_TEST);
        glScissor(xOffset, yOffset, viewportSize, viewportSize);
        glClearColor(DRAWING_AREA_COLOR.r, DRAWING_AREA_COLOR.g, DRAWING_AREA_COLOR.b, DRAWING_AREA_COLOR.a);
        glClear(GL_COLOR_BUFFER_BIT);
        glDisable(GL_SCISSOR_TEST);

        // Update the viewport after resizing
        setupViewport(width, height);

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
                    // Reset translation for the rectangle (or set a different one)
                    glm::vec4 rectangleColor(1.0f, 0.0f, 0.0f, 1.0f); // Roșu
                    glm::vec3 rectangleTranslation(0.0f, 0.0f, 0.0f); // No translation for rectangle
                    unsigned int colorLoc = glGetUniformLocation(shaderProgram.ID, "objectColor");
                    unsigned int rectTransLoc = glGetUniformLocation(shaderProgram.ID, "translation");
                    glUniform3f(rectTransLoc, rectangleTranslation.x, rectangleTranslation.y, rectangleTranslation.z);
                    glUniform4f(colorLoc, rectangleColor.r, rectangleColor.g, rectangleColor.b, rectangleColor.a);
                    rectangle.draw();  // Draw the rectangle
                }
            }
        }
        glm::mat4 model = glm::mat4(1.0f);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        // Resetare sau setare culoare diferită pentru bloc
        glm::vec4 circleColor(0.0f, 0.0f, 1.0f, 1.0f); // Albastru
        unsigned int colorLoc = glGetUniformLocation(shaderProgram.ID, "objectColor");
        glUniform4f(colorLoc, circleColor.r, circleColor.g, circleColor.b, circleColor.a);
        glm::vec3 circleTranslation(0.0f, -0.9f, 0.0f); // Move circle to bottom center
        unsigned int circleTransLoc = glGetUniformLocation(shaderProgram.ID, "translation");
        glUniform3f(circleTransLoc, circleTranslation.x, circleTranslation.y, circleTranslation.z);
        circle.draw();  // Draw the circle

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
