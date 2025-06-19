add_library(game
    Game.cpp
    ManageEvents.cpp
)

target_link_libraries(game PRIVATE
    glm-header-only
    shared-state
)

target_include_directories(game PRIVATE
    ${PROJECT_SOURCE_DIR}/submodules/glm
    ${PROJECT_SOURCE_DIR}/src/Glad/include
    ${PROJECT_SOURCE_DIR}/src
)
