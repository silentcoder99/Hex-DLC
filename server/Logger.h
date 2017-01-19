#pragma once
#include <string>


/*
 * Logger Singleton:
 * Logs to whatever is appropriate. Can be extended upon for logging elsewhere (e.g, to file)
 * if desired. Usually logs to stdout.
 *
 * Use logError when the program cannot continue with what it was doing because of some circumstance
 * Use logWarning when the program can continue, but the outcome probably isn't desirable to the user
 * Use logInfo for logging program activity
 *
 * Debug Level 1: Main events, Starting Server, Connection Requests and such, enough info to show that the program is working
 * Debug Lever 2: Important events, Info of evolving generations, Generation count, Some populations may spam user if neccesary
 * Debug Lever 3: Details on important events, Champions, and the nitty gritty
 *
 */ 

class Logger{
    static Logger* m_instance;
public:
    static Logger* getInstance();

    
    // Use logInfo for logging program activity
    virtual void logInfo(std::string message, int debugLevel) = 0;
    
    // Use logWarning when the program can continue, but the outcome probably isn't desirable to the user
    virtual void logWarning(std::string message) = 0;
    
    // Use logError when the program cannot continue with what it was doing because of some circumstance
    virtual void logError(std::string error) = 0;

};
