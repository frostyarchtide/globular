#include "globular/debug.hpp"

#include <csignal>
#include <iostream>

#include <epoxy/gl.h>

void debug::print_info(std::string message, std::string header) {
    #ifdef NDEBUG
        return;
    #endif

    std::cout
        << "\033[90;1m["
        << header
        << "]\033[0;90m "
        << message
        << "\033[0m"
        << std::endl;
}

void debug::print_warning(std::string message, std::string header) {
    #ifdef NDEBUG
        return;
    #endif

    std::cout
        << "\033[93;1m["
        << header
        << "]\033[0;93m "
        << message
        << "\033[0m"
        << std::endl;
}

void debug::print_error(std::string message, bool trap, std::string header) {
    #ifdef NDEBUG
        return;
    #endif

    std::cerr
        << "\033[91;1m["
        << header
        << "]\033[0;91m "
        << message
        << "\033[0m"
        << std::endl;

    if (trap)
        raise(SIGTRAP);
}

void debug::print_glfw_error(int id, const char* description) {
    #ifdef NDEBUG
        return;
    #endif

    debug::print_error(
        description,
        true,
        (std::string("GLFW ERROR ") + std::to_string(id)).c_str()
    );
}
