#pragma once

#include <string>
#include <iostream>
#include <mutex>

namespace VoxelFactory {
class Logger {
 public:
    static const Logger &getInstance();

    enum logLevel {
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        FATAL
    };
    void log(const std::string &msg,
        const std::string &tag,
        logLevel level = DEBUG) const;

 private:
    mutable std::mutex _mutex;
};
}  // namespace VoxelFactory

std::ostream &operator<<(std::ostream &os,
    const VoxelFactory::Logger::logLevel &level);
