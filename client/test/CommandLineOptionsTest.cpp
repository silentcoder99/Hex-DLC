#define BOOST_TEST_MODULE CommandLineOptionsClient
#include <boost/test/included/unit_test.hpp>
#include <CommandLineOptions.h>

BOOST_AUTO_TEST_CASE( InitializeWithHelpArgument ){
    CommandLineOptions* clo = CommandLineOptions::getInstance();
    char arg0[] = "./HexDLCClient";
    char arg1[] = "--help";
    char* argv[] = {arg0, arg1, NULL};
    clo->setOptions(2, argv);

    BOOST_TEST( clo->helpRequested() );
    
}


BOOST_AUTO_TEST_CASE ( UnkownOption ){
    try{
        char arg0[] = "./HexDLCClient";
        char arg1[] = "--notanoption";
        char* argv[] = {arg0, arg1, NULL};
        CommandLineOptions::getInstance()->setOptions(2,argv);
        BOOST_FAIL( "Incorrect option did not raise exception" ); 
    }catch(UnknownOptionException e){
       // If here, test suceeded, continue 
    }
}
