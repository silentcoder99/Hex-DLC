cmake_minimum_required(VERSION 2.8)
project(Hex-DLC)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

set (SERVER_SRC
	server/FileIO.cpp
	server/genetics/GAlgorithm.cpp
	server/genetics/TournamentSelection.cpp
    server/genetics/Member.cpp

    server/Logger.cpp
    server/log/STDOutLogger.cpp

	server/Game.cpp
	server/MyRandom.cpp
	server/genetics/Network.cpp
	server/Server.cpp
	server/HexDLC.cpp
	server/Source.cpp
	server/WorkerThread.cpp)

set (SERVER_HEADER
	server/FileIO.h
	server/genetics/GAlgorithm.h
	server/genetics/Member.h
	server/genetics/TournamentSelection.h
	server/genetics/SelectionAlgorithm.h

    server/Logger.h
    server/log/STDOutLogger.h

	server/Game.h
	server/MyRandom.h
	server/genetics/Network.h
	server/SuperArray.hpp
	server/Server.h
	server/HexDLC.h
	server/Vec2.hpp
	server/WorkerThread.h)
	
set(CLIENT_SRC
	client/Source.cpp)

set(SERVER_TEST_SRC
	test/Vec2Test.cpp)

include_directories("external/websocketpp")
include_directories("external/pugixml/src")
include_directories("server")

add_subdirectory("external/pugixml")
set(Boost_USE_STATIC_LIBS	ON)
set(Boost_USE_MULTITHREADED	ON)
set(Boost_USE_STATIC_RUNTIME OFF)

set (WEBSOCKET_BOOST_LIBS
	system
	chrono
	regex
	random
	date_time)

find_package( Boost 1.40 COMPONENTS thread ${WEBSOCKET_BOOST_LIBS} REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

find_package( Threads )

# Create project
add_executable(Hex-DLCServer ${SERVER_SRC} ${SERVER_HEADER})

add_executable(Hex-DLCServerTest ${SERVER_TEST_SRC})

set(HexDLCLibraries ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} pugixml) 
# Boost
target_link_libraries(Hex-DLCServer ${HexDLCLibraries})

target_link_libraries(Hex-DLCServerTest ${HexDLCLibraries})

add_executable(Hex-DLCClient ${CLIENT_SRC})
target_link_libraries(Hex-DLCClient ${Boost_LIBRARIES})

target_link_libraries(Hex-DLCClient ${CMAKE_THREAD_LIBS_INIT})

