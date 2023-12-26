#include "timedFileLogger.h"
#include <ctime>
#include <fstream>

TimedFileLogger::TimedFileLogger(const std::string& fileName_): fileName(fileName_){};
void TimedFileLogger::write(const std::string &message) {
    if ((message.empty())) {
            return;
    }
    std::ofstream os(fileName);
    std::time_t result = std::time(nullptr);
    if(fileName.empty()){
        std::cout << "No file to write in!\n";
    }
    os << "TimedFileLogger writes:\n" << message << "\n";
    os << std::ctime(&result) << "\n";
}