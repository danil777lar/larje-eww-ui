#include <fstream>
#include <iostream>
#include <sstream>
#include <charconv>
#include <signal.h>
#include <bits/ostream.tcc>
#include "Window.h"

#include "json.hpp"

using string = std::string;
using json = nlohmann::json;

string root_path;
string window_path;
json config_content;

std::vector<string> widget_commands;
std::vector<pid_t> subprocesses;

Window::Window(const string &root_path, const string &window_path) {
    this->root_path = root_path;
    this->window_path = window_path;

    config_content = parse_config();
    widget_commands = get_widget_commands();
    create_yuck_file();
}

Window::~Window() {
    std::cout << "Delete window " << config_content["name"] << std::endl;
}

void Window::open() {
    subprocesses.clear();
    for (string cmd : widget_commands) {
        run_subprocess("./widgets/" + cmd);
    }
    system(("eww open " + config_content["name"].get<string>()).c_str());
}

void Window::close() {
    for (pid_t pid: subprocesses) {
        kill_subprocess(pid);
    }
    system(("eww close " + config_content["name"].get<string>()).c_str());
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

    for (int i = 0; i < widget_commands.size(); ++i) {
        string name = get_widget_name(widget_commands[i], i);
        yuck_content += "(defvar var-" + name + " \" (label :class 'back' :text '+') \")\n";
    }

    yuck_content += "\n\n";
    yuck_content += "(defwindow " + config_content["name"].get<string>() + "\n";
    for (const nlohmann::basic_json<> &key: config_content["window"]) {
        yuck_content += "  " + key.get<string>() + "\n";
    }

    if (config_content.contains("widgets_root")) {
        yuck_content += get_widgets(config_content["widgets_root"], 0, new std::vector<string>());
    }
    else {
        std::cout << "window.get_yuck_content: no widgets_root found in config" << std::endl;
    }
    yuck_content += ")";

    yuck_content += "\n\n";
    for (int i = 0; i < widget_commands.size(); ++i) {
        string name = get_widget_name(widget_commands[i], i);
        yuck_content += "(defwidget " + name + " []\n";
        yuck_content += "   (literal :content var-" + name + "))\n";
    }

    return yuck_content;
}

string Window::get_widgets(json box, int depth, std::vector<string>* widget_out) const {
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
                string widget_name = get_widget_name(key.get<string>(), widget_out->size());
                string command = key.get<string>() + " --var_name " + "var-" + widget_name;
                widget_out->push_back(command);
                result += spacing + "(" + widget_name + ")" + "\n";
            }
            else {
                result += spacing + get_widgets(key, depth + 1, widget_out);
            }
        }
    }

    result += ")";

    return result;
}

string Window::get_widget_name(string widget_command, int index) const {

    string name = config_content["name"];
    name += "-" + std::to_string(index);
    name += "-" + widget_command.substr(0, widget_command.find(' '));

    return name;
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

std::vector<string> Window::get_widget_commands() const {
    std::vector<string>* tmp = new std::vector<string>();
    get_widgets(config_content["widgets_root"], 0, tmp);
    return *tmp;
}

pid_t Window::run_subprocess(string cmd) {
    std::istringstream iss(cmd);
    std::string token;
    std::vector<char*> args;
    std::vector<std::string> storage;
    while (iss >> token) {
        storage.push_back(token);
    }
    for (auto& str : storage) {
        args.push_back(str.data());
    }
    args.push_back(nullptr);

    pid_t pid = fork();
    if (pid == 0) {
        execvp(args[0], args.data());
        _exit(1);
    }
    else if (pid > 0) {
        return pid;
    }
    else {
        std::cerr << "Fork failed\n";
        return -1;
    }
}

void Window::kill_subprocess(pid_t pid) {
    kill(pid, SIGTERM);
}
