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

void VoxelFactory::Renderer::storeForRendering(const MeshData &meshData)
{
    if (_meshes.contains(meshData.chunkPosition))
        return;

    LOG_DEBUG("Sending mesh to GPU ({}, {}, {})",
        meshData.chunkPosition.x, meshData.chunkPosition.y, meshData.chunkPosition.z);
    auto mesh = std::make_unique<OpenGLUtils::Mesh>(meshData.vertices, meshData.indices);
    _meshes[meshData.chunkPosition] = std::move(mesh);
}

void VoxelFactory::Renderer::renderFrame()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (const auto &[pos, mesh] : _meshes) {
        mesh->draw();
    }

    glfwSwapBuffers(_window);
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
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
    LOG_INFO("Stopped renderer thread");
}
