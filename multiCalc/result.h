#pragma once 
#include <string>
#include "calculator.h"
#include "command.h"

struct Result
{
    private:
    std::string res;
    public:
    Result(const Command & com) {
        res = std::to_string(com.getVal1()) + " " + com.commToStr() + " " + std::to_string(com.getVal2()) + " = ";
        res += std::to_string(Calculator :: execute(com));
    }
    std::string getRes() const {
        return res;
    }

};
