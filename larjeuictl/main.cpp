#include <iostream>
#include <csignal>
#include "WindowController.h"

WindowController* initializer_instance;

void signal_handler(int signal)
{
    delete initializer_instance;
    exit(0);
}

int main()
{
    std::cout << "Starting larjeuictl..." << std::endl;

    signal(SIGTERM, signal_handler);
    signal(SIGINT, signal_handler);
    initializer_instance = new WindowController();

    while (true) {
        sleep(1);
    }

    return 0;
}