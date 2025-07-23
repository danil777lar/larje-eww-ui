#include <chrono>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <unordered_map>

#include "Box.h"
#include "Label.h"
#include "larje_utils.hpp"

using string = std::string;

std::string get_current_time_str() {
    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
    std::time_t t_c = std::chrono::system_clock::to_time_t(now);
    std::tm* local_time = std::localtime(&t_c);

    std::ostringstream oss;
    oss << std::put_time(local_time, "%H:%M:%S");
    return oss.str();
}

int main(int argc, char **argv) {
    std::unordered_map<std::string, std::string> args = process_args(argc, argv);

    int update_time = 1;
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

    Box* back = new Box();
    back->_class = Class("card-default");
    back->_vexpand = VExpand::True;
    back->_hexpand = HExpand::True;

    Label* label = new Label();
    label->_class = Class("label-default");
    label->_vexpand = VExpand::True;
    label->_hexpand = HExpand::True;
    back->addChild(label);

    while (true) {
        label->_text = Text(get_current_time_str());
        var_content = back->serialize();

        string command = "eww update " + eww_var_name + "=\"" + var_content + "\"";
        system(command.c_str());

        sleep(update_time);
    }

    return 0;
}