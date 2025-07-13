#ifndef INITIALIZER_H
#define INITIALIZER_H

#include <vector>
#include <filesystem>

class WindowController {

public:
    WindowController();
    ~WindowController();

private:
    std::vector<std::string> find_window_configs(const std::filesystem::path& root, const std::string& target_name);
};

#endif
