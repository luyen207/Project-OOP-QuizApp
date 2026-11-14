#include "DisplayHelper.h"

#include <cctype>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

// In mot duong ke de phan tach cac khu vuc tren man hinh.
void DisplayHelper::printLine(char symbol, int width) {
    std::cout << std::string(width, symbol) << '\n';
}

// In tieu de man hinh.
void DisplayHelper::printTitle(const std::string& title) {
    printLine();
    std::cout << "| " << std::left << std::setw(60)
              << title << " |\n";
    printLine();
}

// Hien thi tien do dua tren so cau da tra loi.
void DisplayHelper::printProgress(int answered, int total) {
    int percent = 0;

    if (total > 0) {
        percent = answered * 100 / total;
    }

    const int filled = percent / 5;
    const int empty = 20 - filled;

    std::cout << "Tien do: ["
              << std::string(filled, '#')
              << std::string(empty, '-')
              << "] " << percent << "% ("
              << answered << "/" << total << ")\n";
}

// Loai bo khoang trang o dau va cuoi chuoi.
std::string DisplayHelper::trim(const std::string& value) {
    const std::size_t first = value.find_first_not_of(" \t\r\n");

    if (first == std::string::npos) {
        return "";
    }

    const std::size_t last = value.find_last_not_of(" \t\r\n");
    return value.substr(first, last - first + 1);
}

// Chuyen chuoi sang chu hoa de xu ly lenh khong phan biet hoa/thuong.
std::string DisplayHelper::toUpper(std::string value) {
    for (char& character : value) {
        character = static_cast<char>(
            std::toupper(static_cast<unsigned char>(character))
        );
    }

    return value;
}

// Dinh dang so giay thanh phut:giay.
std::string DisplayHelper::formatDuration(long long seconds) {
    if (seconds < 0) {
        seconds = 0;
    }

    std::ostringstream output;
    output << std::setfill('0')
           << std::setw(2) << seconds / 60
           << ":"
           << std::setw(2) << seconds % 60;

    return output.str();
}

// Dinh dang thoi diem bat dau bai thi.
std::string DisplayHelper::formatDateTime(
    std::chrono::system_clock::time_point timePoint
) {
    const std::time_t rawTime =
        std::chrono::system_clock::to_time_t(timePoint);

    std::tm localTime{};

#ifdef _WIN32
    localtime_s(&localTime, &rawTime);
#else
    localtime_r(&rawTime, &localTime);
#endif

    std::ostringstream output;
    output << std::put_time(&localTime, "%d/%m/%Y %H:%M:%S");

    return output.str();
}
