#include <chrono>
#include <lug/Core/Application.hpp>
#include <lug/System/Logger.hpp>

namespace lug {
namespace Core {

Application::Application(const Application::Info& info) : _info{info}, _graphics{info.name, info.version} {}

bool Application::init(int argc, char* argv[]) {
    // TODO: Use argc and argv to parse the command line
    (void)(argc);
    (void)(argv);

    if (!_graphics.init(_graphicsInitInfo)) {
        return false;
    }

    _window = _graphics.getRenderer()->createWindow(_renderWindowInitInfo);
    if (!_window) {
        return false;
    }

    return true;
}

// TODO: Replace with Timer class
float getElapsedTime(std::chrono::high_resolution_clock::time_point& start) {
    auto stop = std::chrono::high_resolution_clock::now();
    return  std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() / 1000.0f;
}

bool Application::run() {
    float elapsed = 0;
    uint32_t frames = 0;
    while (!_closed && _window && _window->isOpen()) {
        // TODO: Replace with Timer class
        auto start = std::chrono::high_resolution_clock::now();
        // Poll events
        {
            lug::Window::Event event;
            while (_window->pollEvent(event)) {
                onEvent(event);
            }
        }

        //auto renderStart = std::chrono::high_resolution_clock::now();
        beginFrame();
        onFrame(getElapsedTime(start));
        endFrame();
        //LUG_LOG.info("RENDER: {}", getElapsedTime(renderStart));

        elapsed += getElapsedTime(start);
        frames++;
        if (elapsed >= 1000.0f) {
            LUG_LOG.info("FPS: {}", frames);
            frames = 0;
            elapsed = 0;
        }
    }

    return true;
}

void Application::close() {
    _closed = true;
}

bool Application::beginFrame() {
    return _graphics.getRenderer()->beginFrame();
}

bool Application::endFrame() {
    return _graphics.getRenderer()->endFrame();
}

} // Core
} // lug