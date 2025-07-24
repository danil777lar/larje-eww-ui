#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <csignal>
#include "WindowController.h"
#include "Window.h"
#include "larje_utils.hpp"

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
        log("Larjeuictl:WindowController", "Current working directory: " + string(cwd));
    } else {
        std::cerr << "getcwd() error" << std::endl;
    }
}

void apply_theme(const string& root_dir) {
    const string theme_path = "styles/palettes/";
    const char* theme_name = std::getenv("LARJEUI_THEME");
    if (theme_name == nullptr) {
        theme_name = "volumen-clean-light";
    }

    string eww_style_content = "@import '" + theme_path + theme_name + "';\n";
    eww_style_content += "@import 'styles/main';";

    const string cmd = "echo \"" + eww_style_content + "\" > " + root_dir + "/eww.scss";
    log("WindowController", "Apply theme: " + cmd);

    system(cmd.c_str());
}

WindowController::WindowController() {
    log("Larjeuictl:WindowController", "Create WindowController instance");

    const string home_dir = std::getenv("HOME") ? std::getenv("HOME") : "~";
    const string root_dir = home_dir + "/.config/eww";

    print_working_directory();
    apply_theme(root_dir);

    system("eww kill");
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

    log("Larjeuictl:WindowController", "Found windows count: " + windows.size());
}

WindowController::~WindowController() {
    log("Larjeuictl:WindowController", "Delete WindowController instance");

    for (Window* win : windows) {
        delete win;
    }
    windows.clear();

    system("eww kill");
}
