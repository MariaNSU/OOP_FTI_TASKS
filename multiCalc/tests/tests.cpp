#include "gtest/gtest.h"
#include "../command.h"
#include "../calculator.h"
#include "../fileIO.h"
#include "../result.h"
#include "../fileInfo.h"

TEST(Calculator, NoErrors) {
    Command c1(CommandType :: add, 10, 15);
    Command c2(CommandType :: div, 100, 5);
    Command c3(CommandType :: add_sq, 10, 15);
    Command c4(CommandType :: sq_add, 10, 15);
    Command c5(CommandType :: mult, 10, 15);
    Command c6(CommandType :: sub, 10, 15);
    
    ASSERT_DOUBLE_EQ(Calculator::execute(c1), 25);
    ASSERT_DOUBLE_EQ(Calculator::execute(c2), 20);
    ASSERT_DOUBLE_EQ(Calculator::execute(c3), 325);
    ASSERT_DOUBLE_EQ(Calculator::execute(c4), 625);
    ASSERT_DOUBLE_EQ(Calculator::execute(c5), 150);
    ASSERT_DOUBLE_EQ(Calculator::execute(c6), -5);
}
TEST(Calculator, ZeroDiv){
    Command c1(CommandType :: div, 4, 0);
    ASSERT_TRUE(std::isnan(Calculator::execute(c1)));
}

TEST(FileIO, readLogFile){
    std::stringstream inp{"dir:MY_DIR\n
                        output:OUTPUT\n
                        numberOfFiles:100\n
                        logging:1"};
    FileIO f;
    f.readLogFile(inp);
    auto fi = f.getFileInf();
    ASSERT_EQ(fi.dirName(), "MY_DIR");
    ASSERT_EQ(fi.outputName(), "OUTPUT");
    ASSERT_EQ(fi.numberOfFiles(), 100);
    ASSERT_EQ(fi.logNeed(), true);
}