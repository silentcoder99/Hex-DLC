#pragma once
#include <string>
#include <vector>

class FileIO {
public:
	static void saveToFile(std::string filename, std::string content);

	static std::string serializeDoubleVector(std::vector<double> vector);
};