//shadersources.h
#ifndef SHADER_SOURCES_H
#define SHADER_SOURCES_H

namespace ShaderSources {
    //game
    inline const char* vertexShaderSource = R"glsl(
        #version 330 core
        layout (location = 0) in vec3 aPos;

        uniform mat4 model;

        void main() {
            gl_Position = model * vec4(aPos, 1.0);
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
