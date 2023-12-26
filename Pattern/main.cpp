#include <iostream>
#include "logger.h"
#include "simpleFileLogger.h"
#include <fstream>

int main()
{   
    SimpleFileLogger SFL("../output.txt");
    Logger L(&SFL);
    L.log_message("xexexex\n");
    
    
}