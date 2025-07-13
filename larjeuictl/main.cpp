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

void enable_log_out(){
    std::string path = "/home/xxemokidxx/.config/eww/log.txt";
        logFile.open(path);

    if (!logFile.is_open()) {
        std::cerr << "Cant open\n";
    }
    else {
        oldCoutBuffer = std::cout.rdbuf();
        std::cout.rdbuf(logFile.rdbuf());
        std::cout << "Log file enabled at: " << path << std::endl;
    }
}

int main()
{
    enable_log_out();

    std::cout << "Starting larjeuictl..." << std::endl;

    signal(SIGTERM, signal_handler);
    signal(SIGINT, signal_handler);
    window_controller = new WindowController();

    while (true) {
        sleep(1);
    }

    return 0;
}