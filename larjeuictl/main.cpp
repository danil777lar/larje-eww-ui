#include <iostream>
#include "larje_utils.hpp"
using string = std::string;

const string KEY_HELP = "--help";
const string KEY_THEME = "--theme-set";
const string KEY_THEME_LIST = "--theme-list";

void try_show_help(std::unordered_map<string, string> args) {
    if (args.contains(KEY_HELP)) {
        std::cout << KEY_HELP << ": Show this help message" << std::endl;
        std::cout << KEY_THEME << ": Set the theme for the application" << std::endl;
        std::cout << KEY_THEME_LIST << ": List available themes" << std::endl;
    }
}

void try_set_theme(std::unordered_map<string, string> args) {
    if (args.contains(KEY_THEME)) {
        string theme = args[KEY_THEME];

        system("mkdir -p ~/.config/environment.d");
        system(("echo \"LARJEUI_THEME=" + theme + "\" > ~/.config/environment.d/larjeui_theme.conf").c_str());
        system("systemctl --user daemon-reexec");
        system("systemctl --user restart larjeuid");

        std::cout << "Theme set to " << theme << std::endl << std::endl;
    }
}

void try_theme_list(std::unordered_map<string, string> args) {
    if (args.contains(KEY_THEME_LIST)) {
        system("systemctl --user restart larjeuid");

        std::cout << "Themes: " << std::endl;
        std::cout << std::endl;
    }
}

int main(int argc, char **argv)
{
    std::unordered_map<string, string> args = process_args(argc, argv);

    if (args.empty()) {
        std::cout << "No arguments provided. Use --help for more information." << std::endl;
        return 0;
    }

    try_show_help(args);
    try_set_theme(args);
    try_theme_list(args);

    return 0;
}