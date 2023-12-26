#include "logger.h"

Logger::Logger(LoggerStrategy* str) : strategy(str){
}
Logger::~Logger(){
    strategy.release();
}
void Logger::log_message(const std::string &message){
    strategy->write(message);
}
void Logger::set_strategy(LoggerStrategy* strategy_){
    strategy.reset(strategy_);
}