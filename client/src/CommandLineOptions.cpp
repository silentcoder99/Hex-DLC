#include "CommandLineOptions.h"

namespace po = boost::program_options;

CommandLineOptions* CommandLineOptions::instance = nullptr;

CommandLineOptions* CommandLineOptions::getInstance(){
    if(instance == nullptr){
        instance = new CommandLineOptions();
    }
    return instance;
}

CommandLineOptions::CommandLineOptions(){
   m_desc.add_options()
      ("help", "produce help message");
}


void CommandLineOptions::setOptions(int argc,char* argv[]){
    try{
    po::store(po::parse_command_line(argc, argv, m_desc), m_optionsGiven);
    }
    catch(po::unknown_option& e){
        throw UnknownOptionException(e.get_option_name());
    }
    po::notify(m_optionsGiven);
}

bool CommandLineOptions::helpRequested(){
    return m_optionsGiven.count("help");
}
