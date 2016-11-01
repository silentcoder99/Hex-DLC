#include "FileIO.h"
#include <sstream>
#include <fstream>

void FileIO::saveWeightsToFile(std::string filename, std::vector<double> vector) {
	std::ofstream outFile(filename);

	if (outFile.is_open()) {
		for (auto element : vector) {
			outFile << element << std::endl;
		}
		outFile.close();
	}

}

std::vector<double> FileIO::readWeightsFromFile(std::string filename) {
	std::vector<double> weights;
	std::ifstream inFile(filename);

	if (inFile.is_open()) {
		std::string line;
		while (std::getline(inFile, line, '\n')) {
			weights.push_back(std::stod(line));
		}
	}

	return weights;
}
