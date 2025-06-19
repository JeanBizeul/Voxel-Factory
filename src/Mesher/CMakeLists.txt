add_library(mesher
    Mesher.cpp
)

target_link_libraries(mesher PRIVATE
    glm-header-only
    shared-state
    opengl-utils
)

target_include_directories(mesher PRIVATE
    ${PROJECT_SOURCE_DIR}/submodules/glm
    ${PROJECT_SOURCE_DIR}/src
)
