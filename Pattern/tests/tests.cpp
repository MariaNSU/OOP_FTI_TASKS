#include "gtest/gtest.h"
#include "../logger.h"
#include "../consoleLogger.h"
#include "../simpleFileLogger.h"
#include "../timedFileLogger.h"
#include <fstream>
#include <string>


TEST(ConsoleLogger, NoErrors) {
    Logger L(new ConsoleLogger);
    L.log_message("test1 message\n");
}

TEST(FileLogger, NoErrors) {
    SimpleFileLogger SFL("../output.txt");
    Logger L(&SFL);
    L.log_message("test2 message\n");
    std::fstream f("../output.txt");
}

