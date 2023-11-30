#include "calculator.h"
#include "command.h"
#include "fileIO.h"
#include <iostream>
#include <fstream>
#include <future>
#include <vector>
#include <algorithm>

void handle(int N, const FileInfo & fileInform, std::ostream & outStrm) {
    FileIO f;
    std::string fileName = fileInform.dirName + "/in_" + std::to_string(N) + ".dat";
    std::fstream inStrm (fileName); 
    Command com = f.getCmd(inStrm);
    f.write(com, outStrm);
}

int main() { 
    FileIO f;
    std::fstream fstr ("logfile.txt");
    f.readLogFile(fstr);
    auto fileInform = f.getFileInf();
    auto numberOfFiles = fileInform.numberOfFiles;
    std::fstream outStrm (fileInform.outputName);

    std::vector <std::future<void>> tasks;
    try {
        for (int i = 1; i <= numberOfFiles; i++){
            auto task = std::async (std::launch::async, handle, i, std::ref(fileInform), std::ref(outStrm));
            tasks.push_back(std::move(task));
        }
    }
    catch (...) {
        std::cout << "exception is here!" << std::endl;
    }
    try {
        for (int i = 0; i < numberOfFiles; i++){
            tasks[i].wait();
        }
    }
    catch(...){
        std::cout << "or exception is here!" << std::endl;
    }
    //std::fstream outStrm ("");

    return 0;
}