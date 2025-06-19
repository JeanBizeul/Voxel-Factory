/*
** EPITECH PROJECT, 2025
** Voxel-Factory
** File description:
** main
*/

#include <iostream>
#include <thread>
#include <csignal>

#include "SharedState/SharedState.hpp"
#include "Mesher/Mesher.hpp"
#include "Game/Game.hpp"
#include "Renderer/Renderer.hpp"
#include "Logger/Logger.hpp"

VoxelFactory::SharedState st;

void sigintHandler(int sig)
{
    (void) sig;

    LOG_INFO("Received SIGINT, stopping app");
    st.stopApp();
}

int main()
{
    std::signal(SIGINT, sigintHandler);
    Logs::Logger::getInstance().setMinimumLogLevel(Logs::LogLevel::Info);
    std::thread mesher(VoxelFactory::chunckMesherThread, std::ref(st));
    std::thread renderer(VoxelFactory::rendererThread, std::ref(st));
    VoxelFactory::gameSimulationThread(std::ref(st));

    st.stopApp();
    mesher.join();
    renderer.join();
    return 0;
}
