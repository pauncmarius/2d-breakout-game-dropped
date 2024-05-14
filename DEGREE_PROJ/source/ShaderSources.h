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
        uniform vec4 objectColor;

        void main() {
            FragColor = objectColor;
        }
    )glsl";

    inline const char* vertexTextShaderSource = R"glsl(
    #version 330 core
    layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
    out vec2 TexCoords;

    uniform mat4 projection;

    void main()
    {
        gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);
        TexCoords = vertex.zw;
} 
)glsl";

    inline const char* fragmentTextShaderSource = R"glsl(
    #version 330 core
    in vec2 TexCoords;
    out vec4 color;

    uniform sampler2D text;
    uniform vec3 textColor;

    void main()
    {    
        vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
        color = vec4(textColor, 1.0) * sampled;
    } 
)glsl";


}

#endif // SHADER_SOURCES_H
