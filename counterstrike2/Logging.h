#pragma once
#include <iostream>
#include <string>
#include <string_view>
#include <format>
#include <winnt.h>
#include <processenv.h>
#include <WinBase.h>
#include <consoleapi2.h>
#include <mutex>
#include <chrono>
#include <ctime>

inline std::mutex mLogging;
inline HANDLE hStdOut = nullptr;

enum class ConColor {
    Black,
    Blue,
    Green,
    Teal,
    Red,
    Lily,
    Yellow,
    White,
    Grey,
    LightBlue,
    LightGreen,
    LightTeal,
    LightRed,
    LightLily,
    LightYellow,
    BrightWhite
};

inline void SetConsoleColor(ConColor text = ConColor::White, ConColor background = ConColor::Black) {
    if (!hStdOut)
        hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)(((WORD)background << 4) | (WORD)text));
}

enum LogPrefix {
    LP_NONE,
    LP_WARNING,
    LP_INFO,
    LP_ERROR,
    LP_DATA
};

inline std::string GetLogPrefix(LogPrefix prefixType) {
    switch (prefixType)
    {
    case LP_WARNING:
        SetConsoleColor(ConColor::LightYellow);
        return "[WARNING] ";
    case LP_INFO:
        SetConsoleColor(ConColor::LightTeal);
        return "[INFO] ";
    case LP_ERROR:
        SetConsoleColor(ConColor::LightRed);
        return "[ERROR] ";
    case LP_DATA:
        SetConsoleColor(ConColor::LightGreen);
        return "[DATA] ";
    }
    return "";
}

inline std::string GetCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm local_time;
    localtime_s(&local_time, &now_time);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &local_time);
    return buffer;
}

template<typename ...Args>
void Log(LogPrefix prefixType, Args&&... args) {
    std::lock_guard<std::mutex> lk(mLogging);
    std::string prefix = GetLogPrefix(prefixType);
    std::string timestamp = GetCurrentTimestamp();
    ((std::cout << "[" << timestamp << "] " << prefix) << ... << args) << '\n';
    SetConsoleColor();
}

// Formatted log
template<typename ...Args>
void LogF(LogPrefix prefixType, const char* fmtString, Args&&... args) {
    std::lock_guard<std::mutex> lk(mLogging);
    std::string prefix = GetLogPrefix(prefixType);
    std::string timestamp = GetCurrentTimestamp();
    std::cout << "[" << timestamp << "] " << prefix << std::vformat(fmtString, std::make_format_args(std::forward<Args>(args)...)) << '\n';
    SetConsoleColor();
}

#if defined(_DEBUG) || defined(_DebugDev)
#define LogInfo(str) Log(LP_INFO, xorstr_(str))
#define LogWarning(str) Log(LP_WARNING, xorstr_(str))
#define LogError(str) Log(LP_ERROR, xorstr_(str))
#define LogData(str) Log(LP_DATA, xorstr_(str))
#else
#define LogInfo(str) 
#define LogWarning(str) 
#define LogError(str) 
#define LogData(str) 
#endif
