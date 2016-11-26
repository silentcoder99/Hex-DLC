#pragma once
#include <string>
#include <vector>
#include "GAlgorithm.h"

class FileIO {
public:
	static std::string doubleArrayToString(Array<double> vector);

	static void saveWeightsToFile(std::string filename, Array<double> vector);
	static std::vector<double> readWeightsFromFile(std::string filename);
	static void savePopToFile(std::string filename, Population population, int generation = 0);
	static Population readPopFromFile(std::string filename);

	static void logPrint(std::string str);
};