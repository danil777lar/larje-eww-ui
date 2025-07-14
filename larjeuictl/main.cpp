#include <iostream>
#include <fstream>
#include <csignal>
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
    std::cout << "Starting larjeuictl...\n" << std::endl;

    signal(SIGTERM, signal_handler);
    signal(SIGINT, signal_handler);
    window_controller = new WindowController();

    while (true) {
        sleep(1);
    }

    return 0;
}