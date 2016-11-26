cmake_minimum_required(VERSION 3.5)
project(Hex-DLC)

set (SERVER_SRC
	server/FileIO.cpp
	server/GAlgorithm.cpp
	server/Game.cpp
	server/MyRandom.cpp
	server/Network.cpp
	server/Server.cpp
	server/HexDLC.cpp
	server/Source.cpp)

set (SERVER_HEADER
	server/FileIO.h
	server/GAlgorithm.h
	server/Game.h
	server/MyRandom.h
	server/Network.h
	server/SuperArray.hpp
	server/Server.h
	server/HexDLC.h
	server/Vec2.hpp)
	
set(CLIENT_SRC
	client/Source.cpp)	

include_directories("external/websocketpp")

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

add_executable(Hex-DLCServer ${SERVER_SRC} ${SERVER_HEADER})
target_link_libraries(Hex-DLCServer ${Boost_LIBRARIES})

target_link_libraries(Hex-DLCServer ${CMAKE_THREAD_LIBS_INIT})

add_executable(Hex-DLCClient ${CLIENT_SRC})
target_link_libraries(Hex-DLCClient ${Boost_LIBRARIES})

target_link_libraries(Hex-DLCClient ${CMAKE_THREAD_LIBS_INIT})

