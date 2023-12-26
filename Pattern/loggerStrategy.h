#pragma once 
#include <iostream>
#include <string>

class LoggerStrategy {
public:
    virtual void write(const std::string &message) = 0;
    virtual ~LoggerStrategy() = default;
};





