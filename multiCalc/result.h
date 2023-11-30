#pragma once 
#include <string>
#include "calculator.h"
#include "command.h"

struct Result
{
    public:
    std::string getRes(const Command & com) {
        std::string res;
        res = std::to_string(com.getVal1()) + " " + com.commToStr() + " " + std::to_string(com.getVal2()) + " = ";
        res += std::to_string(Calculator :: execute(com)) + "\n";
        return res;
    }
};
