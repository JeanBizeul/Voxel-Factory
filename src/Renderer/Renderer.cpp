#include "Renderer.hpp"

#include <thread>

#include "Logger/Logger.hpp"

VoxelFactory::Renderer::Renderer()
{
    Logger::getInstance().log("Loading renderer", "renderer", Logger::INFO);
    // OpenGl stuff
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
    Renderer renderer;

    while (state.running) {
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
