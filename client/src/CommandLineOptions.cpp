#include "CommandLineOptions.h"

CommandLineOptions* CommandLineOptions::instance = nullptr;

CommandLineOptions* CommandLineOptions::getInstance(){
    if(instance == nullptr){
        instance = new CommandLineOptions();
    }
    return instance;
}


void CommandLineOptions::setOptions(int argc,const char* argv[]){
    
}

bool CommandLineOptions::argumentsValid(){
    return false;
}

bool CommandLineOptions::helpRequested(){
    return false;
}
