#pragma once
#include <string>

struct FileInfo {
    
    std::string outputName;
    std::string dirName;
    size_t numberOfFiles = 0;
    bool logNeed = 0;
};