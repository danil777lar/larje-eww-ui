#include <chrono>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <unordered_map>
#include <cmath>

#include "json.hpp"
#include "Label.h"
#include "larje_utils.hpp"
#include "eww_ui/Box.h"

using string = std::string;

string get_widget_name(string widget_command, int index) {

    string name = "";//config_content["name"];
    name += "-" + std::to_string(index);
    name += "-" + widget_command.substr(0, widget_command.find(' '));

    return name;
}

string get_widgets(nlohmann::json box, int depth, std::vector<string>* widget_out) {
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

int main(int argc, char **argv) {
    std::unordered_map<std::string, std::string> args = process_args(argc, argv);

    float update_time = 1;
    string eww_var_name = "";
    if (args.contains("--var_name")) {
        eww_var_name = args["--var_name"];
    }
    else {
        return 0;
    }

    while (true) {
        string var_content = "(box :orientation 'v' :vexpand true :hexpand true (tile-panel-0-widget-clock) (tile-panel-1-widget-battery))";
        string command = "eww update " + eww_var_name + "=\"" + var_content + "\"";
        system(command.c_str());
        sleep(update_time);
    }

    return 0;
}