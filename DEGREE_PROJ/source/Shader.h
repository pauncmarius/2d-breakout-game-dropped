#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>

class Shader {
public:
    unsigned int ID;  // Shader program ID

    // Constructor that builds the shader program from shader source code strings
    Shader(const char* vertexCode, const char* fragmentCode);

    // Destructor
    ~Shader();

    // Use/activate the shader program
    void use();

private:
    // Utility method for checking shader compilation/linking errors.
    void checkCompileErrors(unsigned int shader, const std::string& type);
};

#endif // SHADER_H
