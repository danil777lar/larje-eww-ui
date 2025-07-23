#include <iostream>
#include <fstream>
#include <csignal>

#include "larje_utils.hpp"
#include "WindowController.h"

WindowController* window_controller;
std::ofstream logFile;
std::streambuf* oldCoutBuffer = nullptr;

void signal_handler(int signal)
{
    delete window_controller;
    exit(0);
}

int main()
{
    log("Larjeuictl:main", "Starting larjeuictl...\n");

    signal(SIGTERM, signal_handler);
    signal(SIGINT, signal_handler);

    window_controller = new WindowController();

    sleep(1);
    system("hyprctl reload");

    while (true) {
        sleep(1);
    }

    return 0;
}