#pragma once
#include <variant>

namespace VoxelFactory
{
enum class EventType {
    KeyPressed,
    KeyReleased,
    MouseButtonPressed,
    MouseButtonReleased,
    MouseMoved,
    MouseScrolled
};

struct KeyEvent {
    int key;
};

struct MouseButtonEvent {
    int button;
};

struct MouseMoveEvent {
    double xpos;
    double ypos;
};

struct MouseScrollEvent {
    double xoffset;
    double yoffset;
};

using InputData = std::variant<KeyEvent, MouseButtonEvent, MouseMoveEvent, MouseScrollEvent>;

struct InputEvent {
    EventType type;
    InputData data;
};
} // namespace VoxelFactory
