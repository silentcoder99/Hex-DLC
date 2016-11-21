#include "FileIO.h"
#include <sstream>
#include <fstream>
#include <iostream>

void FileIO::saveWeightsToFile(std::string filename, std::vector<double> vector) {
	std::ofstream outFile(filename);

	if (outFile.is_open()) {
		for (auto element : vector) {
			outFile << element << ",";
		}
		outFile.close();
	}

}

std::vector<double> FileIO::readWeightsFromFile(std::string filename) {
	std::vector<double> weights;
	std::ifstream inFile(filename);

	if (inFile.is_open()) {
		std::string line;
		while (std::getline(inFile, line, ',')) {
			if (!line.empty()) {
				weights.push_back(std::stod(line));
			}
		}
	}

	return weights;
}

void FileIO::savePopToFile(std::string filename, Population population) {
	std::ofstream outFile(filename);

	if (outFile.is_open()) {
		for (int i = 0; i < POP_SIZE; i++) {
			std::vector<double> weights = population.getMember(i).m_network.getWeights();

			for (auto weight : weights) {
				outFile << weight << ",";
			}
			outFile << "\n";
		}
	}
}

Population FileIO::readPopFromFile(std::string filename) {
	std::ifstream inFile(filename);
	Population pop = Population(false);

	if (inFile.is_open()) {
		std::string line;
		while (std::getline(inFile, line, '\n')) {
			if (!line.empty()) {
				std::stringstream  linestream(line);
				std::vector<double> weights;
				std::string weight;

				while (std::getline(linestream, weight, ',')) {
					if (!weight.empty()) {
						weights.push_back(std::stod(weight));
					}
				}
				Member member = Member();
				member.m_network.setWeights(weights);

				pop.addMember(member);
			}
		}
	}

	return pop;
}
