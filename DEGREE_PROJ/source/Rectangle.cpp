//rectangle.cpp
#include "Rectangle.h"
#include <iostream>

Rectangle::Rectangle(float width, float height) {
    float vertices[] = {
        0.0f, 0.0f, 0.0f,  // Bottom-left
        width, 0.0f, 0.0f,  // Bottom-right
        0.0f, height, 0.0f, // Top-left
        width, 0.0f, 0.0f,  // Bottom-right
        0.0f, height, 0.0f, // Top-left
        width, height, 0.0f // Top-right
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Rectangle::~Rectangle() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    std::cout << "Deleting Rectangle VAO and VBO" << std::endl;
}

void Rectangle::draw() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}