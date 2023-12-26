#include "consoleLogger.h"

void ConsoleLogger::write(const std ::string& message) {
    if (message.empty()) {
            return;
    }
    std::cout << "ConsoleLogger writes:\n " << message << std::endl;
}