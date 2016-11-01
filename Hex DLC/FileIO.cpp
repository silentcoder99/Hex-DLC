#include "FileIO.h"
#include <sstream>
#include <fstream>

std::string FileIO::serializeDoubleVector(std::vector<double> vector) {
	std::stringstream ss;
	for (auto element : vector) {
		ss << element << std::endl;
	}
	return ss.str();
}

void FileIO::saveToFile(std::string filename, std::string content) {
	std::ofstream outFile(filename);

	if (outFile.is_open()) {
		outFile << content;
		outFile.close();
	}

}