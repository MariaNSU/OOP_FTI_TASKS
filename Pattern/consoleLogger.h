#pragma once 
#include "loggerStrategy.h"

class ConsoleLogger : public LoggerStrategy {
public:
    void write(const std::string &message) override;
};