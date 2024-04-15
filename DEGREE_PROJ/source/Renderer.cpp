#include "Renderer.h"
#include <glad/glad.h>

Renderer::Renderer() {
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,  // left  
         0.5f, -0.5f, 0.0f,  // right 
         0.0f,  0.5f, 0.0f   // top   
    };
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

Renderer::~Renderer() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Renderer::draw(Shader& shader) {
    shader.use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}
