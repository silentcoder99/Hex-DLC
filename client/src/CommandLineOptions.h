#include <boost/program_options.hpp>
#include <sstream>

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
    void setOptions(int argc,const char* argv[]);
    bool argumentsValid();
    bool helpRequested();    
};

class UnknownOptionException : public std::runtime_error {

public:
    UnknownOptionException(std::string option)
        : runtime_error("Invalid option given"){
        m_option = option;
    }

    virtual const char* what() const throw(){
        std::ostringstream ss;
        ss.str("");

        ss << runtime_error::what() << ": " << m_option;
        return ss.str().c_str();
    }

    std::string getUnkownOption(){
        return m_option;
    }
private:

    std::string m_option;
};
