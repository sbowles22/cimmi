
#include <memory>
#include <fmt/ostream.h>
#include <exception>
#include <fstream>
#include <string>
#include <omp.h>
#include "logger.hpp"

using namespace std;
using namespace cimmi::logger;

std::string cimmi::logger::log_file_name = STRINGIFY(LOGFILE);
// std::unique_ptr<Logger> cimmi::logger::g_log (new Logger(log_file_name));
Logger* cimmi::logger::g_log (new Logger(log_file_name));

Logger::Logger(std::string log_file_name)
{
    omp_init_lock(&writelock);
    log_file = fopen(log_file_name.c_str(), "w");

    if (log_file == NULL) {
        throw runtime_error("Log file unable to open.");
    }

    this -> add_log(Level::Info, "Opened logger.");
}

Logger::~Logger()
{
    this -> add_log(Level::Info, "Closing logger.");
    fclose(log_file);
    omp_destroy_lock(&writelock);
}
