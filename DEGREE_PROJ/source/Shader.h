//shader.h
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>

class Shader {
public:
    unsigned int ID;

    Shader(const char* vertexCode, const char* fragmentCode);
    ~Shader();

    void use();

private:
    void checkCompileErrors(unsigned int shader, const std::string& type);
};

#endif // SHADER_H
