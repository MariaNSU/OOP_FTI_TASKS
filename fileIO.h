#pragma once
#include "command.h"
#include <mutex>
#include <shared_mutex>

namespace {
CommandType defineCmd(const std::string & name){
    CommandType cmd;
    if(name == "add") {
        cmd = CommandType :: add;
    }
    if(name == "div") {
        cmd = CommandType :: div;
    }
    if(name == "mult") {
        cmd = CommandType :: mult;
    }
    if(name == "add_sq") {
        cmd = CommandType :: add_sq;
    }
    if(name == "sq_add") {
        cmd = CommandType :: sq_add;
    }
    if(name == "sub") {
        cmd = CommandType :: sub;
    }
    if(name != "add" && name != "div" && name != "mult" && name != "add_sq" &&  name != "sq_add" && name != "sub"){
        throw std::invalid_argument("Wrong command name!");
    }
    return cmd;
}
} 



class FileIO  {
private:
    mutable std::shared_mutex mtx;
public:
    //Каждый вызов write создавать объект Calculator...Жеееесть.....
    // И зачем сюда std::istream передавать если только в std::cout выводишь
    // И кажется все методы должны быть константными.
    void write(const Command & cmd, std::istream & is ) {
        std::unique_lock lock (mtx);
        Calculator calc;
        auto result = calc.execute(cmd);
        std::cout << cmd.getVal1() << " and " << cmd.getVal2() << " resulted "<< result << "\n!";
        //is >> result;
    }
    // Про исключения написал в тг.
    Command getCmd(std::istream & is) {
        //Слишком много операций захватывает мутекс, попробуй сделать декомпозицию.
        std::shared_lock lock (mtx);
        std::string str;
        getline(is, str);
        if(str.empty()) {
            throw std::invalid_argument("Empty line in file!");
        }
        auto strStream = std::stringstream(str);
        std::string cmdName;
        double val1, val2;
        if(!(strStream >> cmdName)){
            throw std::invalid_argument("Wrong command format!");
        }
        if(!(strStream >> val1)) {
            throw std::invalid_argument("Wrong value1 format!");
        }
        if(!(strStream >> val2)) {
            throw std::invalid_argument("Wrong value2 format!");
        }
        return Command(defineCmd(cmdName),val1,val2);
    }
};

