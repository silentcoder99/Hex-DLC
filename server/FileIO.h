#pragma once
#include <string>
#include <vector>
#include "GAlgorithm.h"

class FileIO {
public:
	static std::string doubleVectorToString(std::vector<double> vector);

	static void saveWeightsToFile(std::string filename, std::vector<double> vector);
	static std::vector<double> readWeightsFromFile(std::string filename);

	static void savePopToFile(std::string filename, Population population);
	static Population readPopFromFile(std::string filename);

	static void logPrint(std::string str);
};