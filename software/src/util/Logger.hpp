#pragma once
#include <iostream>
#include <print>

#define COLOR_RESET "\x1b[0m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_RED "\x1b[31m"
#define LOGGER_BOLD "\033[1m"
#define LOGGER_UNBOLD "\033[0m"

class Logger {
private:
    std::string className;
    template <typename... Args>
    void _log(const std::format_string<Args...> fmt, Args &&...args) {
        std::string out = LOGGER_BOLD;

        out += std::format(fmt, std::forward<Args>(args)...);
        out += LOGGER_UNBOLD;
        std::println("{}", out);
    }

    std::string _getClassName() {
        std::string out = "";
        
        out += this->className;
        if (!this->className.empty()) out += "::";

        return out;
    }

public:
    template <typename... Args>
    void log(const std::format_string<Args...> fmt, Args &&...args) {
        std::print("[{}log] ", this->_getClassName());
        this->_log(fmt, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void warn(const std::format_string<Args...> fmt, Args &&...args) {
        std::print("{}", COLOR_YELLOW);
        std::print("[{}warning] ", this->_getClassName());
        this->_log(fmt, std::forward<Args>(args)...);
        std::print("{}", COLOR_RESET);
    }

    template <typename... Args>
    void error(const std::format_string<Args...> fmt, Args &&...args) {
        std::print("{}", COLOR_RED);
        std::print("[{}error] ", this->_getClassName());
        this->_log(fmt, std::forward<Args>(args)...);
        std::print("{}", COLOR_RESET);
    }

    void setClassName(const std::string name) {
        this->className.assign(name);
    }

    Logger() = default;
    Logger(std::string className) {
        this->className = className;
    }
};