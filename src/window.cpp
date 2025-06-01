#include "globular/debug.hpp"
#include "globular/window.hpp"

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

Window::Window(vec2<unsigned int> resolution, const std::string& title) {
    glfwSetErrorCallback(debug::print_glfw_error);

    if (!glfwInit())
        debug::print_error("Failed to initialize", true, "GLFW ERROR");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window = glfwCreateWindow(resolution.x, resolution.y, title.c_str(), nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        debug::print_error("Failed to create window", true, "GLFW ERROR");
    }

    glfwMakeContextCurrent((GLFWwindow*) window);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    debug::print_info((const char*) glGetString(GL_VERSION), "OPENGL VERSION");

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*) window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    io.IniFilename = NULL;
    io.LogFilename = NULL;
}

Window::~Window() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    if (window)
        glfwDestroyWindow((GLFWwindow*) window);

    glfwTerminate();
}

bool Window::should_close() const {
    return glfwWindowShouldClose((GLFWwindow*) window);
}

void Window::clear(vec4<float> color) {
    glClearColor(color.x, color.y, color.z, color.w);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::update() {
    glfwSwapBuffers((GLFWwindow*) window);
    glfwPollEvents();
}