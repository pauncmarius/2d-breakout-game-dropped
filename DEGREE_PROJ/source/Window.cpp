#include "Window.h"

Window::Window(int width, int height, const char* title) {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        throw std::runtime_error("Failed to initialize GLFW");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        std::cerr << "Failed to create GLFW window\n";
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwDestroyWindow(window);
        glfwTerminate();
        std::cerr << "Failed to initialize GLAD\n";
        throw std::runtime_error("Failed to initialize GLAD");
    }
    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    });
}

Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(window);
}

void Window::swapBuffersAndPollEvents() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}
