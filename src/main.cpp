/*
** EPITECH PROJECT, 2025
** Voxel-Factory
** File description:
** main
*/

#include <iostream>
#include <thread>

#include "SharedState/SharedState.hpp"
#include "Mesher/Mesher.hpp"
#include "Game/Game.hpp"
#include "Renderer/Renderer.hpp"

int main()
{
    VoxelFactory::SharedState st;
    std::thread game(VoxelFactory::gameSimulationThread, std::ref(st));
    std::thread mesher(VoxelFactory::chunckMesherThread, std::ref(st));
    VoxelFactory::rendererThread(std::ref(st));

    std::this_thread::sleep_for(std::chrono::seconds(3));
    st.stopApp();
    game.join();
    mesher.join();
    return 0;
}
