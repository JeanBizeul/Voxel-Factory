add_library(opengl-utils
    Shader.cpp
    VertexBuffer.cpp
    IndexBuffer.cpp
    VertexArray.cpp
    Mesh.cpp
    TextureAtlas.cpp
)

target_link_libraries(opengl-utils PUBLIC
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

target_link_libraries(opengl-utils PRIVATE
    glm-header-only
    shared-state
)

target_include_directories(opengl-utils PRIVATE
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/submodules/glm
    ${PROJECT_SOURCE_DIR}/submodules/glfw/include
)
