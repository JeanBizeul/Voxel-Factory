add_library(renderer
    Renderer.cpp
    FetchInput.cpp
    RendererGettersSetters.cpp
)

target_link_libraries(renderer PRIVATE
    glm-header-only
    shared-state
    logger
    glad
    glfw
    GL
)

target_include_directories(renderer PRIVATE
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/submodules/glm
    ${PROJECT_SOURCE_DIR}/submodules/glfw/include
)
