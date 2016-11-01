#pragma once
#include <string>
#include <vector>

class FileIO {
public:
	static void saveWeightsToFile(std::string filename, std::vector<double> vector);
	static std::vector<double> readWeightsFromFile(std::string filename);

};