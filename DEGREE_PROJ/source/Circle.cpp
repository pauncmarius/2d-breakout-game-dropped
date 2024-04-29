#include "Circle.h"
#include <cmath>

Circle::Circle(float radius, int segments, glm::vec3 initialPosition, glm::vec4 color)
    : radius(radius), segments(segments), position(initialPosition), color(color), VAO(0), VBO(0) {
    setupCircle();
}

Circle::~Circle() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Circle::draw() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, segments + 2);
    glBindVertexArray(0);
}

void Circle::setRadius(float newRadius) {
    radius = newRadius;
    updateVertices();
}

void Circle::setPosition(glm::vec3 newPosition) {
    position = newPosition;
    updateVertices();
}

void Circle::setColor(glm::vec4 newColor) {
    color = newColor;
}

glm::vec3 Circle::getPosition() const {
    return position;
}

glm::vec4 Circle::getColor() const {
    return color;
}

void Circle::updateVertices() {
    vertices.clear();
    vertices.push_back(position.x);  // Centru x
    vertices.push_back(position.y);  // Centru y
    vertices.push_back(0.0f);        // Centru z

    float angleIncrement = 2.0f * 3.14f / segments;
    for (int i = 0; i <= segments; i++) {
        float angle = i * angleIncrement;
        vertices.push_back(position.x + radius * cos(angle)); // x
        vertices.push_back(position.y + radius * sin(angle)); // y
        vertices.push_back(0.0f);                             // z
    }

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
}

void Circle::setupCircle() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    updateVertices();  // Setare inițială a vârfurilor

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
