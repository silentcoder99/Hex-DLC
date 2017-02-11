#include <boost/program_options.hpp>
#include <exception>
#include <stdexcept>

/*
 * Command Line options
 * Interprets the command line options and provides access
 * methods to them
 */
class CommandLineOptions{
    static CommandLineOptions* instance;
    boost::program_options::options_description m_desc;
    boost::program_options::variables_map m_optionsGiven;
protected:
    CommandLineOptions();
public:
    static CommandLineOptions* getInstance();
    void setOptions(int argc,char* argv[]);
    bool argumentsValid();
    bool helpRequested();    
};



/* 
 * Errors that can be thrown when running this class
 */

class UnknownOptionException : public std::runtime_error {

public:
    UnknownOptionException(std::string option)
        : runtime_error("Invalid option given"){
        m_option = option;
        m_message = std::string(runtime_error::what()) + ": " + option;
    }

    virtual const char* what() const throw(){
        return m_message.c_str();

    }

    std::string getUnkownOption(){
        return m_option;
    }
private:
    std::string m_message;
    std::string m_option;
};
