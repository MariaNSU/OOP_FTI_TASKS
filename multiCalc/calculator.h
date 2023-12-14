#pragma once
#include "command.h"
#include <limits>
#include <cmath>


class Calculator final {
private:
    static double add(double val1, double val2) {
        return val1 + val2;
    }
    static double add_sq(double val1, double val2) {
        return val1*val1 + val2*val2;
    }
    static double sq_add(double val1, double val2) {
        return (val1 + val2)*(val1 + val2);
    }
    static double sub(double val1, double val2) {
        return val1 - val2;
    }
    static double mult(double val1, double val2) {
        return val1*val2;
    }
    static double div(double val1, double val2) {
        if(val2 == 0) {
            return std::nan("");
        }
        return val1/val2;
    }
public:
    static double execute(const Command & com) {
        switch (com.getComm()) {
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
                return std::nan("");
        }
    }
};

