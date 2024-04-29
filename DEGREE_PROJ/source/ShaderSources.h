//shadersources.h
#ifndef SHADER_SOURCES_H
#define SHADER_SOURCES_H

namespace ShaderSources {
    // Define shader sources directly in the header
    inline const char* vertexShaderSource = R"glsl(
        #version 330 core
        layout (location = 0) in vec3 aPos;

        uniform mat4 model;
        uniform vec3 translation; // Transformation uniform for moving objects

        void main() {
            gl_Position = model * vec4(aPos + translation, 1.0);
        }
    )glsl";

    inline const char* fragmentShaderSource = R"glsl(
        #version 330 core
        out vec4 FragColor;
        uniform vec4 objectColor; // Adaugă o uniformă pentru culoare

        void main() {
            FragColor = objectColor;
        }
    )glsl";
}

#endif // SHADER_SOURCES_H
