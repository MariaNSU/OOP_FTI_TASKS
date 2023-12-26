#include "simpleFileLogger.h"
#include <fstream>

SimpleFileLogger::SimpleFileLogger(const std::string& fileName_): fileName(fileName_){};
void SimpleFileLogger::write(const std::string &message) {
    if ((message.empty())) {
            return;
    }
    if(fileName.empty()){
        std::cout << "No file to write in!\n";
    }
    std::ofstream os(fileName);
    os << "SimpleFileLogger writes:\n" << message << "\n";
}