#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <mutex>

enum CommandType {add, mult, add_sq, sq_add, sub, div,none};
class Command final {
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
    std::string commToStr() const {
        switch(getComm()) {
            case CommandType :: add:
                return "add";
                break;
            case CommandType :: add_sq:
                return "add_sq";
                break;
            case CommandType :: sq_add:
                return "sq_add";
                break;
            case CommandType :: sub:
                return "sub";
                break;
            case CommandType :: mult:
                return "mult";
                break;
            case CommandType :: div:
                return "div";
                break;
            default:
                return "none";
        }
    }
};
