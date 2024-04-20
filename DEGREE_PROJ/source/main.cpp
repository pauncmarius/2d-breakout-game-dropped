#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
#include "Rectangle.h"
#include "Mat4.h"
#include "ShaderSources.h"

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "Five Rectangles", nullptr, nullptr);
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader shaderProgram(ShaderSources::vertexShaderSource, ShaderSources::fragmentShaderSource);
    Rectangle rectangle(-0.1f, -0.2f, 0.2f, 0.4f);  // A rectangle prototype

    shaderProgram.use();
    float offset = 0.25f; // Space between the centers of the rectangles
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        Mat4 baseModel;
        for (int i = 0; i < 5; i++) {
            Mat4 model = Mat4::translate(baseModel, -0.5f + i * offset, 0.0f);
            unsigned int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model.ptr());
            rectangle.draw();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
