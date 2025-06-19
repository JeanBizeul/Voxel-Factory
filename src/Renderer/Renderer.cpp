#include "Renderer.hpp"

#include <thread>

#include "Logger/Logger.hpp"

VoxelFactory::Renderer::Renderer(SharedState &state)
    : _state(state)
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

    try {
        _blockShader = std::make_unique<OpenGLUtils::Shader>
            ("shaders/block.vert", "shaders/block.frag");
    } catch (std::exception &e) {
        LOG_ERROR(e.what());
    }

    glfwSetWindowUserPointer(_window, &state);
    glfwSetScrollCallback(_window, scrollCallback);
    glfwSetCursorPosCallback(_window, mouseMovedCallback);
}

VoxelFactory::Renderer::~Renderer()
{
    _meshes.clear();
    _blockShader.reset();
    _textureAtlas.reset();

    glfwDestroyWindow(_window);
    glfwTerminate();
}

void VoxelFactory::Renderer::storeForRendering(const MeshData &meshData)
{
    if (_meshes.contains(meshData.chunkPosition))
        return;

    LOG_DEBUG("Sending mesh to GPU ({}, {}, {})",
        meshData.chunkPosition.x, meshData.chunkPosition.y, meshData.chunkPosition.z);
    auto mesh = std::make_unique<OpenGLUtils::Mesh>(meshData.vertices, meshData.indices);
    _meshes[meshData.chunkPosition] = std::move(mesh);
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
            renderer.storeForRendering(meshOpt.value());
        }
        renderer.renderFrame();
        glfwPollEvents();
        if (state.cameraCanMove && !state.cursorTrapped) {
            glfwSetInputMode(renderer.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            state.cursorTrapped = true;
        } else if (!state.cameraCanMove && state.cursorTrapped) {
            glfwSetInputMode(renderer.getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            state.cursorTrapped = false;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(16));

    }
    LOG_INFO("Stopped renderer thread");
}
