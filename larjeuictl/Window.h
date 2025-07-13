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

    private:

    string root_path;
    string window_path;
    json config_content;

    void create_yuck_file() const;
    string get_yuck_content() const;
    string get_widgets(json box, int depth) const;
    json parse_config() const;
};



#endif
