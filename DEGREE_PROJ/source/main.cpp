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

std::vector<std::vector<int>> matrix = {
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
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};


int main() {
    // Inițializarea GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Crearea ferestrei
    int width = 1152, height = 600;
    GLFWwindow* window = glfwCreateWindow(width, height, "Test", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        glfwTerminate();
        return -1;
    }

    // Configurarea shader-ului și a dreptunghiurilor
    Shader shaderProgram(ShaderSources::vertexShaderSource, ShaderSources::fragmentShaderSource);
    shaderProgram.use();

    unsigned int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
    Rectangle rectangle(1.0f, 1.0f);

    // Initialize Circle
    Circle circle(0.3f, 36);  // Create a circle with initial radius 0.5 and 36 segments
    glfwSetWindowUserPointer(window, &circle);

    int rows = matrix.size();
    int cols = matrix[0].size();

    // Loop-ul de redare
    while (!glfwWindowShouldClose(window)) {
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float cellWidth = static_cast<float>(width) / cols;
        float cellHeight = static_cast<float>(height) / rows;

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (matrix[i][j] == 1) {
                    glm::mat4 model = glm::mat4(1.0f);
                    model = glm::translate(model, glm::vec3(
                        -1.0f + 2.0f * (j) / cols,  // Centrarea fiecărui dreptunghi
                        1.0f - 2.0f * (i + 1.0f) / rows,  // in mijlocul celulei sale
                        0.0f
                    ));
                    model = glm::scale(model, glm::vec3(
                        2.0f / cols,   // Scalați pentru a umple celula
                        2.0f / rows,   // fără a depăși
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
        // Resetare sau setare culoare diferită pentru bloc
        glm::vec4 circleColor(0.0f, 0.0f, 1.0f, 1.0f); // Albastru
        unsigned int colorLoc = glGetUniformLocation(shaderProgram.ID, "objectColor");
        glUniform4f(colorLoc, circleColor.r, circleColor.g, circleColor.b, circleColor.a);
        glm::vec3 circleTranslation(-4.5f, -4.1f, 0.0f); // Move circle to bottom center
        unsigned int circleTransLoc = glGetUniformLocation(shaderProgram.ID, "translation");
        glUniform3f(circleTransLoc, circleTranslation.x, circleTranslation.y, circleTranslation.z);
        circle.draw();  // Draw the circle

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
