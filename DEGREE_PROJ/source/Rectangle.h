#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <glad/glad.h>

class Rectangle {
public:
    unsigned int VAO;

    Rectangle(float x, float y, float width, float height);
    ~Rectangle();

    void draw();
};

#endif // RECTANGLE_H
