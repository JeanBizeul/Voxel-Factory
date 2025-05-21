add_subdirectory(Mesher)
add_subdirectory(SharedState)
add_subdirectory(Logger)
add_subdirectory(Game)
add_subdirectory(Renderer)
add_subdirectory(Glad)

add_executable(voxelfactory
    main.cpp
)

target_include_directories(voxelfactory PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)


target_link_libraries(voxelfactory PRIVATE
    glm-header-only
    mesher
    shared-state
    logger
    game
    renderer
)
