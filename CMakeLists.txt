cmake_minimum_required(VERSION 2.8)
project(Hex-DLC)

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

set (SERVER_SRC
	server/util/FileIO.cpp

	server/genetics/Population.cpp
	server/genetics/TournamentSelection.cpp
    server/genetics/Member.cpp
	server/genetics/Network.cpp
    server/genetics/Neuron.cpp
    server/genetics/Layer.cpp

    server/Logger.cpp
    server/log/STDOutLogger.cpp

	server/Game.cpp
	server/MyRandom.cpp
	server/Server.cpp
	server/HexDLC.cpp
	server/Source.cpp
	server/WorkerThread.cpp)

set (SERVER_HEADER
	server/util/FileIO.h
	server/util/FastArray.h
	server/util/Vec2.hpp

	server/genetics/Population.h
	server/genetics/Member.h
	server/genetics/TournamentSelection.h
	server/genetics/SelectionAlgorithm.h
	server/genetics/Network.h
    server/genetics/Neuron.h
    server/genetics/Layer.h

    server/Logger.h
    server/log/STDOutLogger.h

	server/Game.h
	server/MyRandom.h
	server/Server.h
	server/HexDLC.h
	server/WorkerThread.h)
	
set(CLIENT_SRC
	client/Source.cpp)

set(SERVER_TEST_SRC
	test/Vec2Test.cpp)

# External libraries, Websockets and XML
include_directories("external/websocketpp")
include_directories("external/pugixml/src")

# Build pugixml as well
add_subdirectory("external/pugixml")

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
set (HEXDLC_BOOST_LIBS
    thread
    program_options)

# Look for boost
find_package( Boost 1.40 COMPONENTS ${HEXDLC_BOOST_LIBS} ${WEBSOCKET_BOOST_LIBS} REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

# Look for threading libraries
find_package( Threads )

# Create project
add_executable(Hex-DLCServer ${SERVER_SRC} ${SERVER_HEADER})

# Include root directory
target_include_directories(Hex-DLCServer PRIVATE "server")

# Add Tests
add_executable(Hex-DLCServerTest ${SERVER_TEST_SRC})

# Include project directory (files referenced like "server/Game.h")
target_include_directories(Hex-DLCServerTest PRIVATE ".")

# Link required libraries to server and Test
set(HexDLCLibraries ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} pugixml) 
target_link_libraries(Hex-DLCServer ${HexDLCLibraries})
target_link_libraries(Hex-DLCServerTest ${HexDLCLibraries})

# Create client and link required libraries
add_executable(Hex-DLCClient ${CLIENT_SRC})
target_link_libraries(Hex-DLCClient ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} )
