#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include "Shader.h"

class Renderer {
public:
    unsigned int VBO, VAO;

    Renderer();
    ~Renderer();

    void draw(Shader& shader);
};

#endif // RENDERER_H
