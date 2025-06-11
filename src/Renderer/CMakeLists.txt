add_library(renderer
    Renderer.cpp
    FetchInput.cpp
    RendererGettersSetters.cpp
)

target_link_libraries(renderer PUBLIC
    glad
    glfw
    X11
    Xrandr
    Xxf86vm
    Xcursor
    Xinerama
    pthread
    dl
    m
)

target_link_libraries(renderer PRIVATE
    glm-header-only
    shared-state
    logger
    opengl-utils
)

target_include_directories(renderer PRIVATE
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/submodules/glm
    ${PROJECT_SOURCE_DIR}/submodules/glfw/include
)
