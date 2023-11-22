#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <mutex>
#include "calculator.h"

enum CommandType {add, mult, add_sq, sq_add, sub, div};
class Command {
private:
    CommandType Comm;
    double val1 = 0.0;
    double val2 = 0.0;
public:
    Command(CommandType Comm_, double val1_, double val2_ ): Comm(Comm_), val1(val1_), val2(val2_) {};
    Command() = default;
    CommandType getComm() const{
        return Comm;
    }
    double getVal1() const {
        return val1;
    }
    double getVal2() const {
        return val2;
    }
};
