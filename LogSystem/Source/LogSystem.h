#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>

#include "Common.h"

//
class LogSystem
{
public:
    LogSystem() = default;
    ~LogSystem() = default;
public:
    static __forceinline void SetLogFilePath(const std::string& path)
    {
        _path = path;
    }

    static __forceinline std::ofstream& LogFile()
    {
        if (!_logFile.is_open())
            _logFile.open(_path + "Log.txt");
        return _logFile;
    }

    template<typename Head, typename... Args>
    static __forceinline void Log(Head&& head, Args&&... args)
    {
        LogFile() << "Logging\t: ";
        log(std::forward<Head>(head), std::forward<Args>(args)...);
    }

    template<typename Head, typename... Args>
    static __forceinline void LogWarn(Head&& head, Args&&... args)
    {
        LogFile() << "Waring\t: ";
        log(std::forward<Head>(head), std::forward<Args>(args)...);
    }
    template<typename Head, typename... Args>
    static __forceinline void LogError(Head&& head, Args&&... args)
    {
        LogFile() << "Error\t: ";
        log(std::forward<Head>(head), std::forward<Args>(args)...);
    }

    static class Garbage
    {
    public:
        ~Garbage() { _logFile.close(); }
    };
private:
    static __forceinline void log() { _logFile << std::endl; }

    template<typename Head, typename... Args>
    static __forceinline void log(Head&& head, Args&&... args)
    {
        _logFile << std::forward<Head>(head);
        log(std::forward<Args>(args)...);
    }

    template<typename... Args>
    static __forceinline void log(int&& head, Args&&... args)
    {
        _logFile << std::hex << std::forward<int>(head);
        log(std::forward<Args>(args)...);
    }

    template<typename... Args>
    static __forceinline void log(const float head, Args&&... args)
    {
        _logFile << std::hex << std::forward<const float>(head) << "f";
        log(std::forward<Args>(args)...);
    }
    
    template<typename... Args>
    static __forceinline void log(const double head, Args&&... args)
    {
        _logFile << std::hex << std::forward<const double>(head) << "d";
        log(std::forward<Args>(args)...);
    }

    /* glm support sample
    template<typename... Args>
    static __forceinline void log(glm::vec2&& head, Args&&... args)
    {
        _logFile << std::hex
            << std::forward<glm::vec2>(head).x << "f, "
            << std::forward<glm::vec2>(head).y << "f";
        log(std::forward<Args>(args)...);
    }

    template<typename... Args>
    static __forceinline void log(glm::vec3&& head, Args&&... args)
    {
        _logFile << std::hex
            << std::forward<glm::vec3>(head).x << "f, "
            << std::forward<glm::vec3>(head).y << "f, "
            << std::forward<glm::vec3>(head).z << "f";
        log(std::forward<Args>(args)...);
    }
    */
private:
    static Garbage _garbage;
    static std::string _path;
    static std::ofstream _logFile;
};

__forceinline void SetLogFilePath(const std::string& path)
{
    LogSystem::SetLogFilePath(path);
}

template<typename Head, typename... Args>
__forceinline void FLog(Head&& head, Args&&... args)
{
    LogSystem::Log(std::forward<Head>(head), std::forward<Args>(args)...);
}

template<typename Head, typename... Args>
__forceinline void FLogWarn(Head&& head, Args&&... args)
{
    LogSystem::LogWarn(std::forward<Head>(head), std::forward<Args>(args)...);
}

template<typename Head, typename... Args>
__forceinline void FLogError(Head&& head, Args&&... args)
{
    LogSystem::LogError(std::forward<Head>(head), std::forward<Args>(args)...);
}

//
#ifdef _DEBUG
__forceinline void LOG(bool needReturn = true) { if (needReturn) std::cout << std::endl; }

template<typename Head, typename... Args>
__forceinline void LOG(Head&& head, Args&&... args)
{
    std::cout << std::forward<Head>(head);
    LOG(std::forward<Args>(args)...);
}

template<typename... Args>
__forceinline void LOG(std::string&& head, Args&&... args)
{
    std::cout << std::forward<std::string>(head);
    LOG(std::forward<Args>(args)...);
}

template<typename Head, typename... Args>
__forceinline void Log(Head&& head, Args&&... args)
{
    std::cout << "Logging\t: ";
    LOG(std::forward<Head>(head), std::forward<Args>(args)...);
}

template<typename Head, typename... Args>
__forceinline void LogWarn(Head&& head, Args&&... args)
{
    std::cout << "Warning\t: ";
    LOG(std::forward<Head>(head), std::forward<Args>(args)...);
}

template<typename Head, typename... Args>
__forceinline void LogError(Head&& head, Args&&... args)
{
    std::cout << "Error\t: ";
    LOG(std::forward<Head>(head), std::forward<Args>(args)...);
}
#else
#define LOG(context, ...)
#define Log(context, ...)
#define LogWarn(context, ...)
#define LogError(context, ...)
#endif
