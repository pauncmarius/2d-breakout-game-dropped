#ifndef CIRCLE_H
#define CIRCLE_H

#include <glad/glad.h>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>  // Pentru glm::vec4
#include <vector>

class Circle {
public:
    Circle(float radius, int segments, glm::vec3 initialPosition, glm::vec4 color);
    ~Circle();

    void draw();
    void setRadius(float newRadius);
    void setPosition(glm::vec3 newPosition);
    void setColor(glm::vec4 newColor);
    glm::vec3 getPosition() const;
    glm::vec4 getColor() const;

private:
    float radius;
    int segments;
    std::vector<float> vertices;
    GLuint VAO, VBO;
    glm::vec3 position;
    glm::vec4 color;  // Culoarea cercului

    void setupCircle();
    void updateVertices();
};

#endif // CIRCLE_H
