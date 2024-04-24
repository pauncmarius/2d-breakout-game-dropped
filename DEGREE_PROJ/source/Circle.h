//circle.h
#ifndef CIRCLE_H
#define CIRCLE_H

#include <glad/glad.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include <vector>

class Circle {
public:
    Circle(float radius, int segments);
    ~Circle();
    void draw();
    void setRadius(float newRadius);
    void updateVertices();

private:
    unsigned int VAO, VBO;
    float radius;
    int segments;
    std::vector<float> vertices;
    void setupCircle();
};

#endif // CIRCLE_H

