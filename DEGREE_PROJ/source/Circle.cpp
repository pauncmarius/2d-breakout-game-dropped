#include "Circle.h"
#include <cmath>

Circle::Circle(float radius, int segments) {
    vertexCount = segments + 2;  // Extra vertex for the center and the loop closure
    float* vertices = new float[vertexCount * 3];  // Each vertex has x, y, z coordinates

    // Center vertex
    vertices[0] = 0.0f;  // x
    vertices[1] = 0.0f;  // y
    vertices[2] = 0.0f;  // z

    // Generate points around the circle
    for (int i = 1; i < vertexCount; ++i) {
        float angle = 2.0f * M_PI * (i - 1) / (segments);
        vertices[3 * i] = cos(angle) * radius;  // x
        vertices[3 * i + 1] = sin(angle) * radius;  // y
        vertices[3 * i + 2] = 0.0f;  // z
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * 3 * sizeof(float), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    delete[] vertices;  // Clean up vertices array
}

Circle::~Circle() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Circle::draw() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);
    glBindVertexArray(0);
}
