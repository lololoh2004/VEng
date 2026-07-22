#pragma once

#ifdef _WIN32
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
#endif

#include <iostream>
#include <unordered_map>

namespace term{
#ifdef _WIN32
    inline std::string prefix = "win_";
#else
    inline std::string prefix = "lin_";
#endif
    // Example : "warn","\1xb[33m"
    // inline std::unordered_map<std::string, std::string> ansi;
    // Example : "123", "up" (123 is example id)
    inline std::unordered_map<std::string, std::string> control_map;

    inline void clear(){
        std::cout << "\033[H\033[2J" << std::flush;
    }

    inline void ask(std::string_view text){
        std::cout << text << std::flush;
        while (std::cin.get() != '\n');
    }

    template <typename ... Args>
    void msg(Args&&... args){
        (std::cout << ... << args);
    }

    // [[nodiscard]] inline std::string get_ansi(std::string_view name) noexcept {
    //     auto i = ansi.find(std::string(name));
    //     if (i != ansi.end())
    //         return i->second;
    //     return "";
    // }

    [[nodiscard]] inline std::string get_key() noexcept {
        int code = 0;
#ifdef _WIN32
        code = _getch();
        if (code == 0 || code == 224){
            code = _getch();
        }
#else
        struct termios oldt, newt;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        code = getchar();
        if (code == 27) {
            if (getchar() == 91) {
                code = getchar();
            }
        }
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif
        std::string key_name = prefix + std::to_string(code);
        auto content = control_map.find(key_name);
        return content != control_map.end() ? content->second : "";
    }
}
