#include "STDOutLogger.h"
#include <iostream>

STDOutLogger::STDOutLogger(int debugLevel){
    m_debugLevel = debugLevel;
}

void STDOutLogger::logInfo(std::string message, int debugLevel){
    if(debugLevel <= m_debugLevel){
        std::cout << message << std::endl;
    }
}

void STDOutLogger::logWarning(std::string message){
    std::cout << "Warning: " << message << std::endl;
}

void STDOutLogger::logError(std::string message){
    std::cout << "Error: " << message << std::endl;
}
