#include "Renderer.hpp"

void VoxelFactory::Renderer::renderBlocks()
{
    _blockShader->use();
    _blockShader->set("uModel", glm::identity<glm::mat4x4>());
    _blockShader->set("uView", _state.camera().getTransformationMatrix());

    // Obtenir les dimensions de la fenêtre
    int width, height;
    glfwGetFramebufferSize(_window, &width, &height);

    float aspect = static_cast<float>(width) / static_cast<float>(height);
    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f), // FOV en degrés
        aspect,              // ratio largeur / hauteur
        0.1f,                // near plane
        1000.0f              // far plane (à ajuster selon ton monde)
    );

    _blockShader->set("uProjection", projection);

    for (const auto &[pos, mesh] : _meshes) {
        glm::vec3 worldPos = glm::vec3(pos) * CHUNK_SIZE;
        glm::mat4 model = glm::translate(glm::identity<glm::mat4x4>(), worldPos);
        _blockShader->set("uModel", model);
        mesh->draw();
    }
}

void VoxelFactory::Renderer::renderFrame()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderBlocks();

    glfwSwapBuffers(_window);
}
