#include <chrono>
#include <iostream>
#include <sstream>
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

std::string get_current_time_str() {
    auto now = std::chrono::system_clock::now();
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

    while (true) {
        string var_content = "";
        var_content += "(label :vexpand true :hexpand true :class 'back' :text ";
        var_content += "\'" + get_current_time_str() + "\'";
        var_content += " )";

        string command = "eww update " + eww_var_name + "=\"" + var_content + "\"";
        system(command.c_str());

        sleep(update_time);
    }

    return 0;
}