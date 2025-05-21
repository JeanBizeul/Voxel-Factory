#include "Renderer.hpp"

const std::vector<int> keys = {
    GLFW_KEY_W,
    GLFW_KEY_A,
    GLFW_KEY_S,
    GLFW_KEY_D,
    GLFW_KEY_Q,
    GLFW_KEY_E,
    GLFW_KEY_UP,
    GLFW_KEY_DOWN,
    GLFW_KEY_LEFT,
    GLFW_KEY_RIGHT,
    GLFW_KEY_SPACE,
    GLFW_KEY_LEFT_SHIFT
};

const std::vector<int> mouseButtons = {
    GLFW_MOUSE_BUTTON_LEFT,
    GLFW_MOUSE_BUTTON_RIGHT,
    GLFW_MOUSE_BUTTON_MIDDLE,
};

void VoxelFactory::Renderer::fetchInputs(ThreadSafeQueue<InputEvent>& inputEvents, GLFWwindow* window)
{
    for (int key : keys) {
        int state = glfwGetKey(window, key);
        if (state == GLFW_PRESS || state == GLFW_RELEASE) {
            inputEvents.push(InputEvent{
                state == GLFW_PRESS ? EventType::KeyPressed : EventType::KeyReleased,
                KeyEvent{key}
            });
        }
    }

    for (int button : mouseButtons) {
        int state = glfwGetMouseButton(window, button);
        if (state == GLFW_PRESS || state == GLFW_RELEASE) {
            inputEvents.push(InputEvent{
                state == GLFW_PRESS ? EventType::MouseButtonPressed : EventType::MouseButtonReleased,
                MouseButtonEvent{button}
            });
        }
    }

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    inputEvents.push(InputEvent{ EventType::MouseMoved, MouseMoveEvent{xpos, ypos} });
}
