#include "FileIO.h"
#include <sstream>
#include <fstream>
#include <iostream>

std::string FileIO::doubleArrayToString(Array<double> vector)
{
	std::stringstream ss;

	for (int i = 0; i < vector.size(); i++) {
		ss << vector[i] << ",";
	}

	return ss.str();
	
}

void FileIO::saveWeightsToFile(std::string filename, Array<double> vector) {
	std::ofstream outFile(filename);

	if (outFile.is_open()) {
		outFile << doubleArrayToString(vector);
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

void FileIO::savePopToFile(std::string filename, Population population, int generation) {
	std::ofstream outFile(filename);

	if (outFile.is_open()) {
		//Save generation count
		outFile << generation << "\n";

		//Save members
		for (int i = 0; i < POP_SIZE; i++) {
			Array<double> weights = population.getMember(i).m_network.getWeights();

			for (int i = 0; i < weights.size(); i++) {
				outFile << weights[i] << ",";
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

		//Ingnore first line (generation count)
		std::getline(inFile, line);

		while (std::getline(inFile, line, '\n')) {
			if (!line.empty()) {
				std::stringstream  linestream(line);
				std::string weight;
				int weightCount = 0;
				while (std::getline(linestream, weight, ',')) {
					if (!weight.empty()) {
						weightCount++;
					}
				}
				Array<double> weights(weightCount);

				int weightIndex = 0;
				while (std::getline(linestream, weight, ',')) {
					if (!weight.empty()) {
						weights[weightIndex] = std::stod(weight);
						weightIndex++;
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

//Writes to the output stream as well as to log.txt
void FileIO::logPrint(std::string str) {
	std::cout << str;

	std::ofstream outFile;
	outFile.open("log.txt", std::ofstream::out | std::ofstream::app);

	if (outFile.is_open()) {
		outFile << str;
	}
}
