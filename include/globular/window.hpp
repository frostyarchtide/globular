#pragma once

#include "math/vec2.hpp"
#include "math/vec4.hpp"
#include "world.hpp"

class Window : public Resource {
public:
    Window(vec2<unsigned int> resolution = vec2<unsigned int>(800, 600), const std::string& title = "Globular Window");
    ~Window();

    bool should_close() const;
    void clear(vec4<float> color = vec4(0.1f, 0.1f, 0.1f, 1.0f));
    void update();

private:
    void* window;
};