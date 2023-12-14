#include "calculator.h"
#include "command.h"
#include "fileIO.h"
#include <iostream>
#include <fstream>
#include <future>
#include <vector>
#include <algorithm>
#include <ctime>
#include <chrono>

void handle(int N, const FileInfo & fileInform, const FileIO & f, std::ostream & outStrm) {
    std::string fileName = fileInform.dirName + "/in_" + std::to_string(N) + ".dat";
    try {
        std::fstream inStrm (fileName); 
        Command com = f.getCmd(inStrm);
        
    }
    catch(...){
        std::cout << "Exception in handle!\n";
    }
    
}

int main() { 
    FileIO f;
    std::fstream fstr ("logfile.txt");
    f.readLogFile(fstr);
    auto fileInform = f.getFileInf();
    auto numberOfFiles = fileInform.numberOfFiles;
    std::fstream outStrm (fileInform.outputName);
    std::vector <std::future<void>> tasks;

    const auto start{std::chrono::high_resolution_clock::now()};
    for (int i = 1; i <= numberOfFiles; i++){
        auto task = std::async (std::launch::async, handle, i, std::ref(fileInform), std::ref(f), std::ref(outStrm));
        tasks.push_back(std::move(task));
        }

    for (int i = 0; i < numberOfFiles; i++){
        tasks[i].wait();
        }
    std::cout << "exception in threads" << std::endl;
    
    
    const auto finish1{std::chrono::high_resolution_clock::now()};
    for(int i = 1; i <= numberOfFiles; i++) {
        std::string fileName = fileInform.dirName + "/in_" + std::to_string(i) + ".dat";
        std::fstream inStrm (fileName); 
        Command com = f.getCmd(inStrm);
        f.write(com, outStrm,fileInform.logNeed);
    }
    
    const auto finish2{std::chrono::high_resolution_clock::now()};
    const std::chrono::duration<double> elapsed_seconds1{finish1 - start};
    const std::chrono::duration<double> elapsed_seconds2{finish2 - finish1};
    std::cout << "with threads: " << elapsed_seconds1.count() << std::endl;
    std::cout << "with main: " << elapsed_seconds2.count() << std::endl;

    
    return 0;
}