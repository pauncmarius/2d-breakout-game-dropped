#include "Rectangle.h"
#include <iostream>

Rectangle::Rectangle(float x, float y, float width, float height) {
    std::cout << "Creating Rectangle..." << std::endl;

    float vertices[] = {
        // First triangle
        x, y, 0.0f,          // Bottom left
        x + width, y, 0.0f,  // Bottom right
        x, y + height, 0.0f, // Top left

        // Second triangle
        x + width, y, 0.0f,      // Bottom right
        x, y + height, 0.0f,     // Top left
        x + width, y + height, 0.0f // Top right
    };

    glGenVertexArrays(1, &VAO);
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glDeleteBuffers(1, &VBO);
}

Rectangle::~Rectangle() {
    std::cout << "Deleting Rectangle VAO ID: " << VAO << std::endl;
}

void Rectangle::draw() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
