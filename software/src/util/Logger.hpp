#pragma once
#include <iostream>
#include <print>

#define COLOR_RESET "\x1b[0m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_RED "\x1b[31m"
#define BOLD "\033[1m"
#define UNBOLD "\033[0m"

class Logger {
private:
    std::string className;
    template <typename... Args>
    void _log(const std::format_string<Args...> fmt, Args &&...args) {
        std::string out = BOLD;

        if (!this->className.empty())
            out += std::format("{}: ", this->className);

        out += std::format(fmt, std::forward<Args>(args)...);
        out += UNBOLD;
        std::println("{}", out);
    }

public:
    template <typename... Args>
    void log(const std::format_string<Args...> fmt, Args &&...args) {
        std::print("[log] ");
        this->_log(fmt, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void warn(const std::format_string<Args...> fmt, Args &&...args) {
        std::print("{}", COLOR_YELLOW);
        std::print("[warn] ");
        this->_log(fmt, std::forward<Args>(args)...);
        std::print("{}", COLOR_RESET);
    }

    template <typename... Args>
    void error(const std::format_string<Args...> fmt, Args &&...args) {
        std::print("{}", COLOR_RED);
        std::print("[error] ");
        this->_log(fmt, std::forward<Args>(args)...);
        std::print("{}", COLOR_RESET);
    }

    void setClassName(const std::string name) {
        this->className = className;
    }

    Logger() = default;
    Logger(std::string className) {
        this->className = className;
    }
};