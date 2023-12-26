#pragma once 
#include "loggerStrategy.h"

class Logger {
protected:
    std::unique_ptr<LoggerStrategy> strategy;

public:
    Logger(LoggerStrategy* str);
    ~Logger();
    void set_strategy(LoggerStrategy* strategy_);
    void log_message(const std::string &message);
};