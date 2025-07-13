#include <fstream>
#include <iostream>
#include <sstream>
#include <bits/ostream.tcc>
#include "Window.h"
#include "json.hpp"

using string = std::string;
using json = nlohmann::json;

string root_path;
string window_path;
json config_content;

Window::Window(const string &root_path, const string &window_path) {
    this->root_path = root_path;
    this->window_path = window_path;

    config_content = parse_config();
    create_yuck_file();

    system(("eww open " + config_content["name"].get<string>()).c_str());
}

Window::~Window() {
    std::cout << "Delete window " << config_content["name"] << std::endl;
}

void Window::create_yuck_file() const {
    string name = config_content["name"];

    auto path = std::filesystem::path(window_path);
    std::filesystem::path yuck_path = path.parent_path() / (name + ".yuck");

    auto yuck_file = std::ofstream(yuck_path.string());
    yuck_file << get_yuck_content();
    yuck_file.close();
}

string Window::get_yuck_content() const {
    string yuck_content = "";
    yuck_content += "(defwindow " + config_content["name"].get<string>() + "\n";

    for (auto& key : config_content["window"]) {
        yuck_content += "  " + key.get<string>() + "\n";
    }

    if (config_content.contains("widgets_root")) {
        yuck_content += get_widgets(config_content["widgets_root"], 0);
    }
    else {
        std::cout << "window.get_yuck_content: no widgets_root found in config" << std::endl;
    }

    yuck_content += ")";

    return yuck_content;
}

string Window::get_widgets(json box, int depth) const {

    string spacing = "";
    for (int i = 0; i <= depth; ++i) {
        spacing += "  ";
    }

    string result = "";
    result += "(box\n";

    string orientation = "\"" + box.value("orientation", "v") + "\"";
    result += spacing + ":orientation " + orientation + "\n";

    if (box.contains("widgets")) {
        for (auto& key : box["widgets"]) {
            if (key.is_string()) {
                result += spacing + key.get<string>() + "\n";
            }
            else {
                result += spacing + get_widgets(key, depth + 1);
            }
        }
    }

    result += ")";

    return result;
}


json Window::parse_config() const {
    const std::ifstream file(window_path);
    if (!file) return NULL;

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();

    if (content.empty()) NULL;

    json parsed;
    try {
        parsed = json::parse(content);
    }
    catch (const json::parse_error& e) {
        std::cout << "window.get_content: json parsing error" << e.what() << std::endl;
        return NULL;
    }

    return parsed;
}
