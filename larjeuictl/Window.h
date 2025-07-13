#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <json.hpp>
using string = std::string;
using json = nlohmann::json;

class Window
{
    public:

    Window(const string &root_path, const string &window_path);
    ~Window();

    void open();
    void close();

    private:

    string root_path;
    string window_path;
    json config_content;

    std::vector<pid_t> subprocesses;
    std::vector<string> widget_commands;

    void create_yuck_file() const;
    string get_yuck_content() const;
    std::vector<string> get_widget_commands() const;
    string get_widgets(json box, int depth, std::vector<string>* widget_commands) const;
    string get_widget_name(string widget_command, int index) const;
    json parse_config() const;

    pid_t run_subprocess(string cmd);
    void kill_subprocess(pid_t pid);
};



#endif
