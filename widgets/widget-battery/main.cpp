#include <chrono>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <unordered_map>

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

    while (true) {
        string var_content = "";
        var_content += "(label :vexpand true :hexpand true :class 'back' :text ";
        var_content += "\'" + get_current_battery_percent_str() + "\'";
        var_content += ")";


        string command = "eww update " + eww_var_name + "=\"" + var_content + "\"";
        system(command.c_str());

        sleep(update_time);
    }

    return 0;
}