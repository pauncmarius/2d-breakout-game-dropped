//shadersources.h
#ifndef SHADER_SOURCES_H
#define SHADER_SOURCES_H

namespace ShaderSources {
    // Define shader sources directly in the header
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
        void main() {
            FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
        }
    )glsl";
}

#endif // SHADER_SOURCES_H
