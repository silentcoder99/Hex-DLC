
cmake_minimum_required(VERSION 2.8)
project(Hex-DLCClient)

# Use C++ 11 when compiling
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Export all the command line options used to compile
# Application. This is useful if you are using ycm
# Vim completion enging
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set Debug flags for debugging with gcc
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
endif()

# Source files

set(CLIENT_SRC
    src/CommandLineOptions.cpp
    src/Source.cpp)

set(CLIENT_HEADER
    src/CommandLineOptions.h)


# Test Source Files
set(CLIENT_TEST_SRC

    # Tested files
    src/CommandLineOptions.cpp
    
    test/CommandLineOptionsTest.cpp)

set(CLIENT_TEST_HEADER

    src/CommandLineOptions.h)

# External libraries, Websockets and XML
include_directories("../external/websocketpp")

# Boost options
set(Boost_USE_STATIC_LIBS	ON)
set(Boost_USE_MULTITHREADED	ON)
set(Boost_USE_STATIC_RUNTIME OFF)

# Libraries required for websockets
set (WEBSOCKET_BOOST_LIBS
	system
	chrono
	regex
	random
	date_time)

# Boost libraries required to run HexDLC
set (HEXDLCLIENT_BOOST_LIBS
    program_options)

include_directories("src")

# Look for boost
find_package( Boost 1.40 COMPONENTS ${HEXDLCLIENT_BOOST_LIBS} ${WEBSOCKET_BOOST_LIBS} REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

# Look for threading libraries
find_package( Threads )

# Create client and link required libraries
add_executable(Hex-DLCClient ${CLIENT_SRC} ${CLIENT_HEADER})
target_link_libraries(Hex-DLCClient ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} )

# Create test executable
add_executable(Hex-DLCClientTest ${CLIENT_TEST_SRC} ${CLIENT_TEST_HEADER})
target_link_libraries(Hex-DLCClientTest ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
