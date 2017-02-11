#define BOOST_TEST_MODULE CommandLineOptionsClient
#include <boost/test/included/unit_test.hpp>
#include <CommandLineOptions.h>

BOOST_AUTO_TEST_CASE( InitializeWithHelpArgument ){
    CommandLineOptions* clo = CommandLineOptions::getInstance();
    const char* argv[] = {"./HexDLCClient", "--help"};
    clo->setOptions(2, argv);

    BOOST_TEST( clo->helpRequested() );
    
}


BOOST_AUTO_TEST_CASE ( UnkownOption ){
    try{
       const char* argv[] = {"./HexDLCClient", "--notanoption"};
       CommandLineOptions::getInstance()->setOptions(2,argv);
       BOOST_FAIL( "Incorrect option did not raise exception" ); 
    }catch(UnknownOptionException e){
       // If here, test suceeded, continue 
    }
}
