
cmake_minimum_required(VERSION 2.8)
project(Hex-DLCServer)

# Use C++ 11 when compiling
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")

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
	src/util/FileIO.cpp

	src/genetics/Population.cpp
	src/genetics/TournamentSelection.cpp
    src/genetics/Member.cpp
	src/genetics/Network.cpp
    src/genetics/Neuron.cpp
    src/genetics/Layer.cpp

    src/Logger.cpp
    src/log/STDOutLogger.cpp

	src/Game.cpp
	src/MyRandom.cpp
	src/Server.cpp
	src/HexDLC.cpp
	src/Source.cpp
	src/WorkerThread.cpp)

set (SERVER_HEADER
	src/util/FileIO.h
	src/util/FastArray.h
	src/util/Vec2.hpp

	src/genetics/Population.h
	src/genetics/Member.h
	src/genetics/TournamentSelection.h
	src/genetics/SelectionAlgorithm.h
	src/genetics/Network.h
    src/genetics/Neuron.h
    src/genetics/Layer.h

    src/Logger.h
    src/log/STDOutLogger.h

	src/Game.h
	src/MyRandom.h
	src/Server.h
	src/HexDLC.h
	src/WorkerThread.h)

set(SERVER_TEST_SRC
	test/Vec2Test.cpp)


# External libraries, Websockets and XML
include_directories("../external/Simple-Web-Server")
include_directories("external/pugixml/src")

# Build pugixml as well
add_subdirectory("external/pugixml")

# Boost options
set(Boost_USE_STATIC_LIBS	ON)
set(Boost_USE_MULTITHREADED	ON)
set(Boost_USE_STATIC_RUNTIME OFF)

# Libraries required for websockets
set (REST_BOOST_LIBS
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
find_package( Boost 1.40 COMPONENTS ${HEXDLC_BOOST_LIBS} ${REST_BOOST_LIBS} REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

# Look for threading libraries
find_package( Threads )

# Create project
add_executable(Hex-DLCServer ${SERVER_SRC} ${SERVER_HEADER})

# Include root directory
target_include_directories(Hex-DLCServer PRIVATE "src")

# Add Tests
add_executable(Hex-DLCServerTest ${SERVER_TEST_SRC})

# Include project directory 
target_include_directories(Hex-DLCServerTest PRIVATE "src")

# Link required libraries to server and Test
set(HexDLCLibraries ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} pugixml) 
target_link_libraries(Hex-DLCServer ${HexDLCLibraries})
target_link_libraries(Hex-DLCServerTest ${HexDLCLibraries})
