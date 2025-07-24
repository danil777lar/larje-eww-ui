#include <chrono>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <unordered_map>
#include <cmath>

#include "Label.h"
#include "larje_utils.hpp"
#include "eww_ui/Box.h"

using string = std::string;

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