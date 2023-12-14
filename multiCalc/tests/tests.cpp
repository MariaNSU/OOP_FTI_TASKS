#include "gtest/gtest.h"
#include "../command.h"
#include "../calculator.h"
#include "../fileIO.h"
#include "../result.h"
#include "../fileInfo.h"

#include <fstream>
#include <future>
#include <vector>
#include <algorithm>
#include <ctime>
#include <chrono>
const double err = 1.e-7;

void handle(int N, const FileIO & f, std::ostream & outStrm) {
    std::string fileName =  "../input/in_" + std::to_string(N) + ".dat";
    std::fstream inStrm (fileName); 
    Command com = f.getCmd(inStrm);
    f.write(com, outStrm,0);
}

TEST(Calculator, NoErrors) {
    Command c1(CommandType :: add, 10, 15);
    Command c2(CommandType :: div, 100, 5);
    Command c3(CommandType :: add_sq, 10, 15);
    Command c4(CommandType :: sq_add, 10, 15);
    Command c5(CommandType :: mult, 10, 15);
    Command c6(CommandType :: sub, 10, 15);
    
    ASSERT_NEAR(Calculator::execute(c1), 25, err);
    ASSERT_NEAR(Calculator::execute(c2), 20, err);
    ASSERT_NEAR(Calculator::execute(c3), 325, err);
    ASSERT_NEAR(Calculator::execute(c4), 625, err);
    ASSERT_NEAR(Calculator::execute(c5), 150, err);
    ASSERT_NEAR(Calculator::execute(c6), -5, err);
}
TEST(Calculator, ZeroDiv){
    Command c1(CommandType :: div, 4, 0);
    ASSERT_TRUE(std::isnan(Calculator::execute(c1)));
}

TEST(FileIO, readLogFile) {
    std::stringstream inp {"dir:MY_DIR\n"
                        "output:OUTPUT\n"
                        "numberOfFiles:100\n"
                        "logging:1"};
    FileIO f;
    f.readLogFile(inp);
    auto fi = f.getFileInf();
    ASSERT_EQ(fi.dirName, "MY_DIR");
    ASSERT_EQ(fi.outputName, "OUTPUT");
    ASSERT_EQ(fi.numberOfFiles, 100);
    ASSERT_EQ(fi.logNeed, true);
};

TEST(FileIO, readLogFile_Errors) {
    std::stringstream inp {"dr:MY_DIR\n"
                        "outputOUTPUT\n"
                        "number:100\n"
                        "logging:y"};
    FileIO f;
    f.readLogFile(inp);
    auto fi = f.getFileInf();
    ASSERT_EQ(fi.dirName, "");
    ASSERT_EQ(fi.outputName, "");
    ASSERT_EQ(fi.numberOfFiles, 0);
    ASSERT_EQ(fi.logNeed, false);
};


TEST(FileIO, getCmd) {
    std::stringstream inp1 {"add_sq 3 4"};
    std::stringstream inp2 {"add 3 4"};
    std::stringstream inp3 {"mult 3 4"};
    std::stringstream inp4 {"sq_add 3 4"};
    std::stringstream inp5 {"div 3 4"};
    std::stringstream inp6 {"sub 3 4"};
    FileIO f;
    Command com = f.getCmd(inp1);
    ASSERT_EQ(com.commToStr(), "add_sq");
    ASSERT_EQ(com.getVal1(), 3);
    ASSERT_EQ(com.getVal2(), 4);

    com = f.getCmd(inp2);
    ASSERT_EQ(com.commToStr(), "add");
    ASSERT_EQ(com.getVal1(), 3);
    ASSERT_EQ(com.getVal2(), 4);

    com = f.getCmd(inp3);
    ASSERT_EQ(com.commToStr(), "mult");
    ASSERT_EQ(com.getVal1(), 3);
    ASSERT_EQ(com.getVal2(), 4);

    com = f.getCmd(inp4);
    ASSERT_EQ(com.commToStr(), "sq_add");
    ASSERT_EQ(com.getVal1(), 3);
    ASSERT_EQ(com.getVal2(), 4);

    com = f.getCmd(inp5);
    ASSERT_EQ(com.commToStr(), "div");
    ASSERT_EQ(com.getVal1(), 3);
    ASSERT_EQ(com.getVal2(), 4);

    com = f.getCmd(inp6);
    ASSERT_EQ(com.commToStr(), "sub");
    ASSERT_EQ(com.getVal1(), 3);
    ASSERT_EQ(com.getVal2(), 4);
};

TEST(FileIO, getCmd_Errors) {
    std::stringstream inp1 {"addsq 3 4"};
    std::stringstream inp2 {"add 3 a"};
    std::stringstream inp3 {"mult  4"};
    std::stringstream inp4 {"sq_ad 3 4"};
    std::stringstream inp5 {"div 3w 4"};
    std::stringstream inp6 {"sub"};
    FileIO f;
    Command com = f.getCmd(inp1);
    ASSERT_EQ(com.commToStr(), "none");
    ASSERT_EQ(com.getVal1(), 0);
    ASSERT_EQ(com.getVal2(), 0);

    com = f.getCmd(inp2);
    ASSERT_EQ(com.commToStr(), "none");
    ASSERT_EQ(com.getVal1(), 0);
    ASSERT_EQ(com.getVal2(), 0);

    com = f.getCmd(inp3);
    ASSERT_EQ(com.commToStr(), "none");
    ASSERT_EQ(com.getVal1(), 0);
    ASSERT_EQ(com.getVal2(), 0);

    com = f.getCmd(inp4);
    ASSERT_EQ(com.commToStr(), "none");
    ASSERT_EQ(com.getVal1(), 0);
    ASSERT_EQ(com.getVal2(), 0);

    com = f.getCmd(inp5);
    ASSERT_EQ(com.commToStr(), "none");
    ASSERT_EQ(com.getVal1(), 0);
    ASSERT_EQ(com.getVal2(), 0);

    com = f.getCmd(inp6);
    ASSERT_EQ(com.commToStr(), "none");
    ASSERT_EQ(com.getVal1(), 0);
    ASSERT_EQ(com.getVal2(), 0);
};
TEST(Threads, numOfFiles1000){
    int numberOfFiles = 1000;
    std::fstream outStrm ("../../output/test.dat");
    FileIO f;
    std::vector <std::future<void>> tasks;

    const auto start{std::chrono::high_resolution_clock::now()};
    for (int i = 1; i <= numberOfFiles; i++){
        auto task = std::async (std::launch::async, handle, i, std::ref(f), std::ref(outStrm));
        tasks.push_back(std::move(task));
    }
    for (int i = 0; i < numberOfFiles; i++){
        tasks[i].wait();
    }
    
    const auto finish1{std::chrono::high_resolution_clock::now()};
    for(int i = 1; i <= numberOfFiles; i++) {
        std::string fileName =  "../../input/in_" + std::to_string(i) + ".dat";
        std::fstream inStrm (fileName); 
        Command com = f.getCmd(inStrm);
        f.write(com, outStrm,0);
    }
    const auto finish2{std::chrono::high_resolution_clock::now()};
    const std::chrono::duration<double> elapsed_seconds1{finish1 - start};
    const std::chrono::duration<double> elapsed_seconds2{finish2 - finish1};

    ASSERT_TRUE(elapsed_seconds2.count() > elapsed_seconds1.count());
}
TEST(Threads, numOfFiles500){
    int numberOfFiles = 500;
    std::fstream outStrm ("../../output/test.dat");
    FileIO f;
    std::vector <std::future<void>> tasks;

    const auto start{std::chrono::high_resolution_clock::now()};
    for (int i = 1; i <= numberOfFiles; i++){
        auto task = std::async (std::launch::async, handle, i, std::ref(f), std::ref(outStrm));
        tasks.push_back(std::move(task));
    }
    for (int i = 0; i < numberOfFiles; i++){
        tasks[i].wait();
    }
    
    const auto finish1{std::chrono::high_resolution_clock::now()};
    for(int i = 1; i <= numberOfFiles; i++) {
        std::string fileName =  "../../input/in_" + std::to_string(i) + ".dat";
        std::fstream inStrm (fileName); 
        Command com = f.getCmd(inStrm);
        f.write(com, outStrm,0);
    }
    const auto finish2{std::chrono::high_resolution_clock::now()};
    const std::chrono::duration<double> elapsed_seconds1{finish1 - start};
    const std::chrono::duration<double> elapsed_seconds2{finish2 - finish1};
    
    ASSERT_TRUE(elapsed_seconds2.count() > elapsed_seconds1.count());
}

TEST(Threads, numOfFiles100){
    int numberOfFiles = 100;
    std::fstream outStrm ("../../output/test.dat");
    FileIO f;
    std::vector <std::future<void>> tasks;

    const auto start{std::chrono::high_resolution_clock::now()};
    for (int i = 1; i <= numberOfFiles; i++){
        auto task = std::async (std::launch::async, handle, i, std::ref(f), std::ref(outStrm));
        tasks.push_back(std::move(task));
    }
    for (int i = 0; i < numberOfFiles; i++){
        tasks[i].wait();
    }
    
    const auto finish1{std::chrono::high_resolution_clock::now()};
    for(int i = 1; i <= numberOfFiles; i++) {
        std::string fileName =  "../../input/in_" + std::to_string(i) + ".dat";
        std::fstream inStrm (fileName); 
        Command com = f.getCmd(inStrm);
        f.write(com, outStrm,0);
    }
    const auto finish2{std::chrono::high_resolution_clock::now()};
    const std::chrono::duration<double> elapsed_seconds1{finish1 - start};
    const std::chrono::duration<double> elapsed_seconds2{finish2 - finish1};
    
    ASSERT_TRUE(elapsed_seconds2.count() > elapsed_seconds1.count());
}