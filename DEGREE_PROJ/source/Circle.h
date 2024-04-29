#ifndef CIRCLE_H
#define CIRCLE_H

#include <glad/glad.h>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>  // Pentru glm::vec4
#include <vector>

class Circle {
public:
    Circle(float radius, int segments, glm::vec3 newVelocity);
    ~Circle();

    void draw();
    void update(float deltaTime);

private:
    glm::vec3 velocity;  // Add velocity attribute
    float radius;
    int segments;
    std::vector<float> vertices;
    GLuint VAO, VBO;
    glm::vec3 position;
    const double PI = 3.14159265358979323846;

    void setupCircle();
    void updateVertices();
};

#endif // CIRCLE_H
