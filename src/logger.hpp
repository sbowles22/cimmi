
#ifndef FILE_LOGGER_H
#define FILE_LOGGER_H

#include <memory>
#include <fmt/ostream.h>
#include <exception>
#include <fstream>
#include <string>
#include <omp.h>
// #include <format>

#ifdef __GNUC__
#define NORETURN_ATTR __attribute__((noreturn))
#define PRINTF_ATTR(f, a) __attribute__((format(printf, f, a)))
#else
#define NORETURN_ATTR
#define PRINTF_ATTR(f, a)
#endif

// maybe move this to something that isn't compile time
#ifndef LOGFILE
#define LOGFILE log.txt
#endif
#define STRINGIFY(X) #X

// Log level macros :D
#define FATAL(f, ...)   cimmi::logger::log(cimmi::logger::Level::Fatal,   f, ##__VA_ARGS__);
#define ERROR(f, ...)   cimmi::logger::log(cimmi::logger::Level::Error,   f, ##__VA_ARGS__);
#define WARNING(f, ...) cimmi::logger::log(cimmi::logger::Level::Warning, f, ##__VA_ARGS__);
#define INFO(f, ...)    cimmi::logger::log(cimmi::logger::Level::Info,    f, ##__VA_ARGS__);
#define DEBUG(f, ...)   cimmi::logger::log(cimmi::logger::Level::Debug,   f, ##__VA_ARGS__);

namespace cimmi::logger
{   
    enum class Level {
        Fatal=0,
        Error=1,
        Warning=2,
        Info=3,
        Debug=4
    };

    // Initialize the log.
    void startLog(const std::string& filepath);

    // Log a message.
    template<typename ...Args>
    void log(cimmi::logger::Level s, fmt::format_string<Args...> format, Args&&...args);

    class Logger
    {
    private:
        omp_lock_t writelock;
        FILE* log_file;
        std::string levels[5] = {"Fatal", "Error", "Warning", "Info", "Debug"};
    public:
        Logger(std::string log_file_name);
        ~Logger();

        template<typename ...Args>
        void add_log(Level s, fmt::format_string<Args...> format, Args&&...args);
    };

    extern std::string log_file_name;
    extern std::unique_ptr<Logger> g_log;

    template<typename ...Args>
    void log(Level s, fmt::format_string<Args...> format, Args&&...args) {
        g_log -> add_log(s, format, std::forward<Args>(args)...);
    }
    
    template<typename ...Args>
    void Logger::add_log(Level s, fmt::format_string<Args...> format, Args&&...args) {
        omp_set_lock(&writelock);
        fmt::print(log_file, "[{}] ", levels[(int) s]);
        fmt::print(log_file, format, std::forward<Args>(args)...);
        fmt::print(log_file, "\n");
        fflush(log_file);
        omp_unset_lock(&writelock);
    }
} // namespace cimmi::logger

#endif
