#include "Renderer.hpp"

#include <thread>

#include "Logger/Logger.hpp"

VoxelFactory::Renderer::Renderer(SharedState &state)
{
    Logger::getInstance().log("Loading renderer", "renderer", Logger::INFO);
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    _window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, NULL, NULL);
    if (_window == NULL) {
        Logger::getInstance().log("Failed to create GLFW window", "renderer", Logger::FATAL);
        state.running = false;
        return;
    }
    glfwMakeContextCurrent(_window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        Logger::getInstance().log("Failed to initialize GLAD", "renderer", Logger::FATAL);
        state.running = false;
        return;
    }
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}

VoxelFactory::Renderer::~Renderer()
{
    glfwTerminate();
}

void VoxelFactory::Renderer::uploadMeshToGPU(const MeshData &mesh)
{
    // OpenGL stuff
}

void VoxelFactory::Renderer::storeForRendering(const glm::ivec3 pos)
{
    _meshMap.insert(pos);
}

void VoxelFactory::Renderer::renderFrame()
{
    Logger::getInstance().log("Rendering " + std::to_string(_meshMap.size())
        + " meshes", "renderer");
    // OpenGL stuff
}

void VoxelFactory::rendererThread(SharedState &state)
{
    Renderer renderer(state);

    while (state.running) {
        renderer.fetchInputs(state.inputEvents, renderer.getWindow());
        while (!state.readyMeshes.empty()) {
            auto meshOpt = state.readyMeshes.try_pop();

            if (!meshOpt.has_value()) break;
            MeshData mesh = meshOpt.value();
            renderer.uploadMeshToGPU(mesh);
            renderer.storeForRendering(mesh.chunkPosition);
        }
        renderer.renderFrame();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
    Logger::getInstance().log("Stopped renderer thread", "renderer", Logger::INFO);
}
