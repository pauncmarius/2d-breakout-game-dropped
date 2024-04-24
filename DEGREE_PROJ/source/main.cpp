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

void window_size_callback(GLFWwindow* window, int width, int height) {
    std::cout << "Window size changed: " << width << " x " << height << std::endl;
    glViewport(0, 0, width, height);
}

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

    glfwSetWindowSizeCallback(window, window_size_callback);
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
    Circle ball(0.5f, 36);

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
                    rectangle.draw();
                }
            }
        }

        ball.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
