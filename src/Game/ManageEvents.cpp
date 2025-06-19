#include "Game.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "SharedState/Camera.hpp"
#include "Logger/Logger.hpp"

void VoxelFactory::Game::manageEvents(SharedState &state)
{
    while (!state.inputEvents.empty()) {
        auto inputOpt = state.inputEvents.try_pop();
        if (!inputOpt.has_value()) break;

        const auto &event = inputOpt.value();
        std::visit([&](auto&& ev) {
            using T = std::decay_t<decltype(ev)>;
            if constexpr (std::is_same_v<T, KeyEvent>) {
                if (event.type == EventType::KeyPressed)
                    _handleKeyPressed(ev.key, state);
                else
                    _handleKeyRelease(ev.key, state);
            } else if constexpr (std::is_same_v<T, MouseMoveEvent>) {
                _handleMouseMouve(ev.xpos, ev.ypos, state);
            } else if constexpr (std::is_same_v<T, MouseScrollEvent>) {
                _handleMouseScroll(ev.xoffset, ev.yoffset, state);
            } else if constexpr (std::is_same_v<T, MouseButtonEvent>) {
                if (event.type == EventType::MouseButtonPressed)
                    _handleMouseButtonPressed(ev.button, state);
                else
                    _handleMouseButtonReleased(ev.button, state);
            }
        }, event.data);
    }
}

void VoxelFactory::Game::_handleKeyPressed(int key, SharedState &state)
{
    switch (key) {
        case GLFW_KEY_W:
            state.camera().move(Camera::Direction::Up, _deltaTime);
            break;
        case GLFW_KEY_S:
            state.camera().move(Camera::Direction::Down, _deltaTime);
            break;
        case GLFW_KEY_A:
            state.camera().move(Camera::Direction::Left, _deltaTime);
            break;
        case GLFW_KEY_D:
            state.camera().move(Camera::Direction::Right, _deltaTime);
            break;
        case GLFW_KEY_ESCAPE:
            state.stopApp();
            break;
        default:
            break;
    }
}

void VoxelFactory::Game::_handleKeyRelease(int key, SharedState &state)
{
}

void VoxelFactory::Game::_handleMouseButtonPressed(int button, SharedState &state)
{
    switch (button) {
        case GLFW_MOUSE_BUTTON_MIDDLE:
            state.cameraCanMove = true;
            break;
        default:
            break;
    }
}

void VoxelFactory::Game::_handleMouseButtonReleased(int button, SharedState &state)
{
    switch (button) {
        case GLFW_MOUSE_BUTTON_MIDDLE:
        state.cameraCanMove = false;
            break;
        default:
            break;
    }
}

void VoxelFactory::Game::_handleMouseMouve(double deltaX, double deltaY, SharedState &state)
{
    constexpr float sensitivity = 0.1f;
    state.camera().rotateHorizontal(deltaX * sensitivity);
    state.camera().rotateVertical(deltaY * sensitivity);
}

void VoxelFactory::Game::_handleMouseScroll(double x, double y, SharedState &state)
{
    if (y != 0) state.camera().zoom(-y);
}

