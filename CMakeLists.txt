cmake_minimum_required(VERSION 3.5)
project(Hex-DLC)

set (SRC
	src/FileIO.cpp
	src/GAlgorithm.cpp
	src/Game.cpp
	src/MyRandom.cpp
	src/Network.cpp
	src/Source.cpp)

set (HEADER
	src/FileIO.h
	src/GAlgorithm.h
	src/Game.h
	src/MyRandom.h
	src/Network.h
	src/SuperArray.hpp
	src/Vec2.hpp)
	
include_directories("external/websocketpp")

add_executable(Hex-DLCServer ${SRC} ${HEADER})