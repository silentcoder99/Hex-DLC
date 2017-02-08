
/*
 * Command Line options
 * Interprets the command line options and provides access
 * methods to them
 */
class CommandLineOptions{
    static CommandLineOptions* instance;

public:
    static CommandLineOptions* getInstance();
    void setOptions(int argc,const char* argv[]);
    bool argumentsValid();
    bool helpRequested();    
};
