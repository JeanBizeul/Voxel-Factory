add_library(renderer
    Renderer.cpp
)

target_link_libraries(renderer PRIVATE
    glm-header-only
    glfw
    shared-state
    logger
)

target_include_directories(renderer PRIVATE
    ${PROJECT_SOURCE_DIR}/submodules/glm
    ${PROJECT_SOURCE_DIR}/src
)
