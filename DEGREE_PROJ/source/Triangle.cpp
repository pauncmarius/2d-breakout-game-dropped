#include "Triangle.h"
#include <iostream>

Triangle::Triangle() {
    static bool firstTime = true;
    if (firstTime) {
        std::cout << "Creating Triangle..." << std::endl;
        firstTime = false; // Set false to avoid repeating this message
    }

    float vertices[] = {
    -0.8f, -0.8f, 0.0f,  // Bottom Left of first triangle
     0.8f, -0.8f, 0.0f,  // Bottom Right of first triangle and second triangle
    -0.8f,  0.8f, 0.0f,  // Top Left of first triangle and second triangle

    -0.8f,  0.8f, 0.0f,  // Top Left of second triangle (repeated)
     0.8f, -0.8f, 0.0f,  // Bottom Right of second triangle (repeated)
     0.8f,  0.8f, 0.0f   // Top Right of second triangle
    };


    unsigned int VBO;
    glGenVertexArrays(1, &VAO);
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

Triangle::~Triangle() {
    std::cout << "Deleting Triangle VAO ID: " << VAO << std::endl;
}

void Triangle::draw() {
    static bool firstDraw = true;
    if (firstDraw) {
        std::cout << "Drawing Triangle..." << std::endl;
        firstDraw = false; // Set false to avoid repeating this message
    }
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
