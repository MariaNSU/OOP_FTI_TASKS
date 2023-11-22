#pragma once
#include "command.h"
#include <limits>

class Calculator {
private:
    double add(double val1, double val2) {
        return val1 + val2;
    }
    double add_sq(double val1, double val2) {
        return val1*val1 + val2*val2;
    }
    double sq_add(double val1, double val2) {
        return (val1 + val2)*(val1 + val2);
    }
    double sub(double val1, double val2) {
        return val1 - val2;
    }
    double mult(double val1, double val2) {
        return val1*val2;
    }
    double div(double val1, double val2) {
        return val1/val2;
    }
public:
    double execute(const Command & com) {
        CommandType com_ = com.getComm();
        switch (com_) {
            case CommandType :: add:
                return add(com.getVal1(), com.getVal2());
                break;
            case CommandType :: add_sq:
                return add_sq(com.getVal1(), com.getVal2());
                break;
            case CommandType :: sq_add:
                return sq_add(com.getVal1(), com.getVal2());
                break;
            case CommandType :: sub:
                return sub(com.getVal1(), com.getVal2());
                break;
            case CommandType :: mult:
                return mult(com.getVal1(), com.getVal2());
                break;
            case CommandType :: div:
                return div(com.getVal1(), com.getVal2());
                break;
            default:
                return std::numeric_limits<double>::max();
        }
    }
};

