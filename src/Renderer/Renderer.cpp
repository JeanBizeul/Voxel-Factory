#include "Renderer.hpp"

#include <thread>

#include "Logger/Logger.hpp"

VoxelFactory::Renderer::Renderer(SharedState &state)
{
    LOG_INFO("Loading renderer");
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    _window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, NULL, NULL);
    if (_window == NULL) {
        LOG_FATAL("Failed to create GLFW window");
        state.running = false;
        return;
    }
    glfwMakeContextCurrent(_window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        LOG_FATAL("Failed to initialize GLAD");
        state.running = false;
        return;
    }
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    _textureAtlas.reset(new OpenGLUtils::TextureAtlas("assets/textures", 8, 8));
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
    // OpenGL stuff
}

void VoxelFactory::rendererThread(SharedState &state)
{
    Renderer renderer(state);

    LOG_INFO("Started renderer thread");
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
    LOG_INFO("Stopped renderer thread");
}
