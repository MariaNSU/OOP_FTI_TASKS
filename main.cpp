#include "calculator.h"
#include "command.h"
#include "fileIO.h"
#include <iostream>
#include <fstream>
#include <future>
#include <vector>

void handle(int N) {
    std::string fileName = "input/in_";
    fileName += std::to_string(N) + ".dat";
    std::fstream inStrm (fileName);
    std::fstream outStrm ("output/out.dat");
    FileIO f;
    Command com = f.getCmd(inStrm);
    f.write(com, outStrm);
}

int main() {
    int numberOfFiles = 4;
    std::vector <std::future<void>> tasks;
    for (int i = 1; i <= numberOfFiles; i++){
        auto task = std::async (std::launch::async, handle, i);
        tasks.push_back(std::move(task));
    }
    for (int i = 1; i <= numberOfFiles; i++){
        tasks[i].wait();
    }

    return 0;
}