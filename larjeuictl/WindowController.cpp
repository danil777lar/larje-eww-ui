#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <csignal>
#include "WindowController.h"
#include "Window.h"

using string = std::string;
namespace fs = std::filesystem;

std::vector<string> WindowController::find_window_configs(const fs::path& root, const string& target_name)
{
    std::vector<string> configs = {};

    try {
        for (const auto& entry : fs::recursive_directory_iterator(root)) {
            if (entry.is_regular_file() && entry.path().filename() == target_name) {
                configs.push_back(entry.path().string());
            }
        }
    }
    catch (const fs::filesystem_error& e){}

    return configs;
}

void print_working_directory() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != nullptr) {
        std::cout << "Current working directory: " << cwd << std::endl;
    } else {
        std::cerr << "getcwd() error" << std::endl;
    }
}

WindowController::WindowController() {
    print_working_directory();
    system("eww kill");

    const string home_dir = std::getenv("HOME") ? std::getenv("HOME") : "~";
    const string root_dir = home_dir + "/.config/eww";
    const string file_name = "window.json";

    const std::vector<string> windows_configs = find_window_configs(root_dir, file_name);
    for (const string& win : windows_configs){
        Window* window_instance = new Window(root_dir, win);
        windows.push_back(window_instance);
    }

    system("eww daemon");

    while (system("pgrep -x eww > /dev/null") != 0) {
        sleep(0.1);
    }

    for (Window* win : windows) {
        win->open();
    }

    std::cout << "Found windows count: " << windows.size() << std::endl;
}

WindowController::~WindowController() {
    for (Window* win : windows) {
        delete win;
    }
    windows.clear();

    system("eww kill");
}
