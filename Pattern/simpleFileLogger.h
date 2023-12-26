#pragma once 

#include "loggerStrategy.h"

class SimpleFileLogger : public LoggerStrategy {
private:
    std::string fileName;
public:
    SimpleFileLogger() = default;
    SimpleFileLogger(const std::string& fileName_);
    void write(const std::string &message) override;
};