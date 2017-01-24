#pragma once
#include <string>
#include <vector>
#include "genetics/GAlgorithm.h"

class FileIO {
public:
	static std::string doubleArrayToString(Array<double> vector);
	static Array<double> stringToDoubleArray(std::string string);

	static void saveWeightsToFile(std::string filename, Array<double> vector);
	static std::vector<double> readWeightsFromFile(std::string filename);

	static void logPrint(std::string str);
};
