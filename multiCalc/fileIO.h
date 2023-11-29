#pragma once
#include "command.h"
#include "result.h"
#include "fileInfo.h"
#include <mutex>
#include <shared_mutex>
#include <algorithm>

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
        std::cout << "Wrong command name!" << std::endl;
    }
    return cmd;
}
} 



class FileIO final  {
private:
//проблема, если храним ссылку
    FileInfo fi;
    mutable std::shared_mutex mtx;

public:
    FileIO () {
        fi.dirName = "";
        fi.logNeed = 0;
        fi.numberOfFiles = 0;
        fi.outputName = "";
    } ;
    
    void write(const Command & cmd, std::istream & is ) const{
        Result r (cmd);
        {
            std::unique_lock<std::shared_mutex> lock (mtx);
            std::cout << r.getRes() << std::endl;
            //is >> result;
        }
    }
    Command getCmd(std::istream & is) {
        std::string str;
        {
            std::shared_lock<std::shared_mutex> lock (mtx);
            getline(is, str);
        }
    
        if(str.empty()) {
            std::cout << "Empty line in file: " << str << std::endl; 
        }
        auto strStream = std::stringstream(str);
        std::string cmdName;
        double val1, val2;
        if(!(strStream >> cmdName)){
            std::cout << "Wrong command format: " << str << std::endl; 
        }
        if(!(strStream >> val1)) {
            std::cout << "Wrong value1 format: " << str << std::endl; 
        }
        if(!(strStream >> val2)) {
            std::cout << "Wrong value2 format: " << str << std::endl; 
        }
        return Command(defineCmd(cmdName),val1,val2);
    }
    void readLogFile(std::istream & inp) {
        std::string str;
        while (inp >> str) {
            auto pos = str.find_first_of(":");
            if(pos == std::string::npos) {
                return;
            }
            if(str.substr(0,pos) == "dir" && ((pos + 1) < str.size())){
                fi.dirName = str.substr(pos + 1);
            }
            if(str.substr(0,pos) == "output" && ((pos + 1) < str.size())){
                fi.outputName = str.substr(pos + 1);
            }
            if(str.substr(0,pos) == "numberOfFiles" && ((pos + 1) < str.size())){
                if(std::stoi(str.substr(pos + 1)) <= 0) {
                    return;
                }
                fi.numberOfFiles = std::stoi(str.substr(pos + 1));
            }
            if(str.substr(0,pos) == "logging" && ((pos + 1) < str.size())){
                if(std::stoi(str.substr(pos + 1)) <= 0) {
                    return;
                }
                fi.logNeed = std::stoi(str.substr(pos + 1));
            }
        }
    }
    void coutFileInf() const {
        std::cout << "Directory name: " << fi.dirName << "\n";
        std::cout << "Output file name: " << fi.outputName << "\n";
        std::cout << "Number of files: " << fi.numberOfFiles << "\n";
        std::cout << "Logging need: " << fi.logNeed << "\n";
    }
    FileInfo getFileInf() const {
        return fi;
    }
};

