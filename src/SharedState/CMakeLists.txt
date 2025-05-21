add_library(shared-state
    SharedState.cpp
    Camera.cpp
)

target_link_libraries(shared-state PUBLIC
    glm-header-only
    mesher
)

target_include_directories(shared-state PRIVATE
    ${PROJECT_SOURCE_DIR}/submodules/glm
    ${PROJECT_SOURCE_DIR}/src
)
