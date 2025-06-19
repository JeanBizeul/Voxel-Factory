#include "Renderer.hpp"

static ThreadSafeQueue<VoxelFactory::InputEvent> *InputEventsPtr = nullptr;

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
    GLFW_KEY_LEFT_SHIFT,
    GLFW_KEY_ESCAPE
};

const std::vector<int> mouseButtons = {
    GLFW_MOUSE_BUTTON_LEFT,
    GLFW_MOUSE_BUTTON_RIGHT,
    GLFW_MOUSE_BUTTON_MIDDLE,
};

void VoxelFactory::scrollCallback(GLFWwindow *, double xoffset, double yoffset)
{
    if (InputEventsPtr) {
        InputEventsPtr->push(VoxelFactory::InputEvent{
            VoxelFactory::EventType::MouseScrolled,
            VoxelFactory::MouseScrollEvent{xoffset, yoffset}
        });
    }
}

void VoxelFactory::mouseMovedCallback(GLFWwindow *window, double xpos, double ypos)
{
    static double lastMouseX = -1;
    static double lastMouseY = -1;
    static bool firstTimeMoved = true;

    if (firstTimeMoved) {
        lastMouseX = xpos;
        lastMouseY = ypos;
        firstTimeMoved = false;
        return;
    }

    double deltaX = xpos - lastMouseX;
    double deltaY = ypos - lastMouseY;
    lastMouseX = xpos;
    lastMouseY = ypos;

    // Only push event if camera is in move mode
    SharedState* state = reinterpret_cast<SharedState*>(glfwGetWindowUserPointer(window));
    if (state && state->cameraCanMove) {
        state->inputEvents.push(InputEvent{
            EventType::MouseMoved,
            MouseMoveEvent{ deltaX, deltaY }
        });
    }
}

void VoxelFactory::Renderer::fetchInputs(ThreadSafeQueue<InputEvent>& inputEvents, GLFWwindow* window)
{
    InputEventsPtr = &inputEvents;
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
}
