#pragma once 
#include "loggerStrategy.h"

class TimedFileLogger : public LoggerStrategy {
private:
    std::string fileName;
public:
    TimedFileLogger(const std::string& fileName_);
    void write(const std::string &message) override;
};