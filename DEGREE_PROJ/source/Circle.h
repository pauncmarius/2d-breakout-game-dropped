#ifndef CIRCLE_H
#define CIRCLE_H

#include <glad/glad.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class Circle {
public:
    unsigned int VAO, VBO;
    Circle(float radius, int segments);
    ~Circle();
    void draw();
private:
    int vertexCount;  // Keep track of the number of vertices
};

#endif // CIRCLE_H
