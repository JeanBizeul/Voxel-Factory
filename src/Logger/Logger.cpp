#include "Logger.hpp"

#include <iostream>
#include <mutex>
#include <ctime>

namespace VoxelFactory {

const Logger& Logger::getInstance()
{
    static Logger instance;
    return instance;
}

static std::string getTimestamp()
{
    std::time_t timestamp = std::time(&timestamp);
    struct std::tm datetime = *std::localtime(&timestamp);

    return std::to_string(datetime.tm_hour)
        + ":" + std::to_string(datetime.tm_min)
        + ":" + std::to_string(datetime.tm_sec);
}

void Logger::log(const std::string& msg, const std::string& tag, logLevel level) const
{
    if (level < ERROR) {
#ifdef _DEBUG
        std::lock_guard<std::mutex> lock(_mutex);
        std::cout << level << "\t" << getTimestamp() << "\t[" << tag << "]\t" << msg << std::endl;
#endif
    } else {
        std::lock_guard<std::mutex> lock(_mutex);
        std::cout << level << "\t" << getTimestamp() << "\t[" << tag << "]\t" << msg << std::endl;
    }
}

} // namespace VoxelFactory

std::ostream& operator<<(std::ostream& os, const VoxelFactory::Logger::logLevel& level)
{
    using LL = VoxelFactory::Logger::logLevel;
    switch (level)
    {
    case LL::DEBUG:   os << "\033[36m[DEBUG]\033[0m"; break;
    case LL::INFO:    os << "\033[32m[INFO]\033[0m"; break;
    case LL::WARNING: os << "\033[33m[WARNING]\033[0m"; break;
    case LL::ERROR:   os << "\033[31m[ERROR]\033[0m"; break;
    case LL::FATAL:   os << "\033[41m[FATAL]\033[0m"; break;
    default:          os << "[UNKNOWN]"; break;
    }
    return os;
}
