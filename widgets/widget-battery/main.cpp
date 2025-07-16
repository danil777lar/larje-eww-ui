#include <chrono>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <unordered_map>

#include "Label.h"
#include "eww_ui/Box.h"

using string = std::string;

std::unordered_map<std::string, std::string> process_args(int argc, char **argv) {
    std::unordered_map<std::string, std::string> args;
    for (int i = 1; i < argc; ++i) {
        std::string key = argv[i];

        if (key.rfind("--", 0) == 0 && (i + 1 < argc)) {
            std::string value = argv[i + 1];
            args[key] = value;
            ++i;
        }
    }
    return args;
}

std::string get_current_battery_percent_str() {
    std::string path = "/sys/class/power_supply/BAT0/capacity";
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Cant open " << path << std::endl;
        return "";
    }

    int percentage;
    file >> percentage;
    return std::to_string(percentage);
}

int main(int argc, char **argv) {
    std::unordered_map<std::string, std::string> args = process_args(argc, argv);

    int update_time = 5;
    if (args.contains("--update_time")) {
        update_time = atoi(args["--update_time"].c_str());
    }

    string eww_var_name = "";
    if (args.contains("--var_name")) {
        eww_var_name = args["--var_name"];
    }
    else {
        return 0;
    }

    string var_content = "";

    /*Box* box = new Box();
    box->_class = Class("back");
    box->_orientation = Orientation::Vertical;
    box->_spaceEvenly = SpaceEvenly::True;
    box->_vexpand = VExpand::True;
    box->_hexpand = HExpand::True;*/

    Label* label = new Label();
    label->_class = Class("back");
    label->_vexpand = VExpand::True;
    label->_hexpand = HExpand::True;
    //box->addChild(label);

    label->_text = Text(get_current_battery_percent_str());
    //var_content = box->serialize();
    var_content = label->serialize();

    system(("wl-copy '" + var_content + "'").c_str());
    std::cout << var_content << std::endl;

    while (true) {
        label->_text = Text(get_current_battery_percent_str());
        //var_content = box->serialize();
        var_content = label->serialize();
        string command = "eww update " + eww_var_name + "=\"" + var_content + "\"";
        system(command.c_str());
        sleep(update_time);
    }

    return 0;
}