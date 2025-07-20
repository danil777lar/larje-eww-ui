#ifndef UTILS_H
#define UTILS_H

#include <chrono>
#include <iostream>
#include <string>

using string = std::string;

inline string get_current_time(const string& format = "%H:%M:%S");
inline void log(const string& source, const string& message);

inline void log(const string& source, const string& message){
    string time = get_current_time();
    std::cout << "[" << time << "] " << "[" << source << "] " << message << std::endl;
}

inline string get_current_time(const string& format){
    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
    std::time_t t_c = std::chrono::system_clock::to_time_t(now);
    std::tm* local_time = std::localtime(&t_c);

    std::ostringstream oss;
    oss << std::put_time(local_time, format.c_str());
    return oss.str();
}

#endif
