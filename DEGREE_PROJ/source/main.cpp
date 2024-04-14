#include "Window.cpp"
#include "Shader.cpp"
#include "Renderer.cpp"

int main() {
    try {
        Window window(800, 600, "OpenGL Example");
        Shader shader("shaders/vertexShader.vert", "shaders/fragmentShader.frag");
        Renderer renderer;

        while (!window.shouldClose()) {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            renderer.draw(shader);

            window.swapBuffersAndPollEvents();
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return -1;
    }
    return 0;
}
