#pragma once

#include <chrono>
#include <string>

// Cac ham tien ich dung chung cho giao dien console.
class DisplayHelper {
public:
    static void printLine(char symbol = '=', int width = 64);
    static void printTitle(const std::string& title);
    static void printProgress(int answered, int total);

    static std::string trim(const std::string& value);
    static std::string toUpper(std::string value);
    static std::string formatDuration(long long seconds);
    static std::string formatDateTime(
        std::chrono::system_clock::time_point timePoint
    );
};
