#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <iostream>
#include "initializer.h"
#include "window.h"

using string = std::string;
namespace fs = std::filesystem;

std::vector<string> find_window_configs(const fs::path& root, const string& target_name)
{
    std::vector<string> configs = {};

    try
    {
        for (const auto& entry : fs::recursive_directory_iterator(root))
        {
            if (entry.is_regular_file() && entry.path().filename() == target_name)
            {
                configs.push_back(entry.path().string());
            }
        }
    }
    catch (const fs::filesystem_error& e)
    {

    }

    return configs;
}

void initializer::initialize()
{
    const string home_dir = std::getenv("HOME") ? std::getenv("HOME") : "~";
    const string root_dir = home_dir + "/.config/eww";
    const string file_name = "window.json";

    const std::vector<string> windows = find_window_configs(root_dir, file_name);
    for (const string& w : windows)
    {
        window(root_dir, w);
    }

    std::cout << "Found windows count: " << windows.size() << std::endl;
}