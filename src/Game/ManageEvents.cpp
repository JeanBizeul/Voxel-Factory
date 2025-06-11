#include "Game.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "SharedState/Camera.hpp"

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
            } else if constexpr (std::is_same_v<T,MouseScrollEvent>) {
                _handleMouseScroll(ev.xoffset, ev.yoffset, state);
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
    default:
        break;
    }
}

void VoxelFactory::Game::_handleKeyRelease(int key, SharedState &state)
{
}

void VoxelFactory::Game::_handleMouseMouve(double x, double y, SharedState &state)
{
    if (x != 0) state.camera().rotateHorizontal(x);
    if (y != 0) state.camera().rotateVertical(y);
}

void VoxelFactory::Game::_handleMouseScroll(double x, double y, SharedState &state)
{
    if (y != 0) state.camera().zoom(y);
}

