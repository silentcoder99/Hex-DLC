#include <iostream>
#include <math.h>
#include <fstream>
#include "MyRandom.h"
#include "Network.h"
#include "Game.h"
#include "GAlgorithm.h"
#include "FileIO.h"

//Log Parameters
#define LOG true
#define MEMBER_SAVE 10 //How frequently the best member is saved
#define POP_SAVE 10 //How frequently the population is saved


int main() {

	Population pop = Population(true);
	int generation = 1;

	//Load initial population from startup file is one exists
	std::ifstream infile("startup.txt");
	if (infile.is_open()) {

		//Load generation count
		std::string str;
		std::getline(infile, str);
		generation = std::stoi(str) + 1;

		infile.close();
		FileIO::logPrint("Loading initial population from startup file\n");

		pop = FileIO::readPopFromFile("startup.txt");
	}
	else {
		FileIO::logPrint("Startup file not found, generating initial population\n");
	}

	//Evolve population
	for (generation; generation <= GENERATION_COUNT; generation++) {

		FileIO::logPrint("Evolving generation " + std::to_string(generation) + "\n");

		pop = Population::evolve(pop);

		//Save population
		if (generation % POP_SAVE == 0) {
			FileIO::savePopToFile("Population " + std::to_string(generation) + ".txt", pop, generation);
		}

		//Save member
		if (generation % MEMBER_SAVE == 0) {
			pop.sortMembers();

			std::vector<double> weights = pop.getMember(POP_SIZE - 1).m_network.getWeights();
			FileIO::saveWeightsToFile("Member " + std::to_string(generation) + ".txt", weights);
		}
	}
	FileIO::logPrint("Finished Evolution\n");

	
	//Save weights and population to file
	pop.scoreMembers();
	pop.sortMembers();

	std::vector<double> weights = pop.getMember(POP_SIZE - 1).m_network.getWeights();
	FileIO::saveWeightsToFile("Member " + std::to_string(GENERATION_COUNT - 1) + ".txt", weights);

	FileIO::savePopToFile("Population " + std::to_string(GENERATION_COUNT - 1) + ".txt", pop, generation);



	////Log a test game against the two best AI's
	/*pop.sortMembers();

	std::vector<double> weights = pop.getMember(POP_SIZE - 1).m_network.getWeights();
	FileIO::saveWeightsToFile("Awesome Guy 1.txt", weights);

	weights = pop.getMember(POP_SIZE - 2).m_network.getWeights();
	FileIO::saveWeightsToFile("Awesome Guy 2.txt", weights);

	pop.startMatch(pop.getMember(POP_SIZE - 1), pop.getMember(POP_SIZE - 2), true);*/

	

	//Network Test
	/*Network net = Network(2, { 2 }, 1);
	net.setWeights({ 1, 0, 0, 0.5, 1.341597, 0, 101, 7.4, 0 });

	std::cout << "New Network Weights:\n";
	std::vector<double> weights = net.getWeights();
	for (auto weight : weights) {
		std::cout << weight << " ";
	}
	std::cout << "\n\n";

	std::cout << "Network output: " << net.getOutput({ 0.5, 0.5 })[0] << "\n";
	std::cout << "Total Weights: " << net.getNumWeights() << "\n";*/

	// Save Weights of champion
	//std::vector<double> wieghts = pop.getMember(0).m_network.getWeights();
	//FileIO::saveWeightsToFile("Champ.txt", wieghts);
	// Read Weights
	//std::vector<double> recoveredWeights = FileIO::readWeightsFromFile("Champ.txt");


	std::cout << "\n";
	std::getchar();
	return 0;
}