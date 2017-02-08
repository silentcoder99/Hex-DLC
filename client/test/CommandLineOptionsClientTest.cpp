#define BOOST_TEST_MODULE CommandLineOptionsClient
#include <boost/test/included/unit_test.hpp>
#include <client/CommandLineOptions.h>

BOOST_AUTO_TEST_CASE( InitializeWithHelpArgument ){
    CommandLineOptions* clo = CommandLineOptions::getInstance();
    const char* argv[] = {"./HexDLCClient", "--help"};
    clo->setOptions(2, argv);

    BOOST_TEST( clo->argumentsValid() ); 
    BOOST_TEST( clo->helpRequested() );
    
}
