//shadersources.h
#ifndef SHADER_SOURCES_H
#define SHADER_SOURCES_H

namespace ShaderSources {
    //game
    inline const char* vertexShaderSource = R"glsl(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec3 instancePos;  // Instance position attribute

        uniform mat4 model;

        void main() {
            vec3 transformedPos = aPos + instancePos;  // Apply instance-specific translation
            gl_Position = model * vec4(transformedPos, 1.0);
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
