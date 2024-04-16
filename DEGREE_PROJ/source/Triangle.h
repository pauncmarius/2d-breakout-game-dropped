//triangle.h
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <glad/glad.h>

class Triangle {
public:
    unsigned int VAO;

    Triangle();
    ~Triangle();

    void draw();
};

#endif // TRIANGLE_H
