#include "Logger.h"
#include "log/STDOutLogger.h"

Logger* Logger::m_instance = nullptr;

Logger* Logger::getInstance(){
    if(m_instance == nullptr){
        m_instance = new STDOutLogger(1);
    }
    return m_instance;
}
