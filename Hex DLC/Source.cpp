#include <iostream>
#include <math.h>
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

	for (int i = 0; i < GENERATION_COUNT; i++) {
		FileIO::logPrint("Evolving generation " + std::to_string(i) + "\n");

		pop = Population::evolve(pop);

		//Save population
		if (i != 0 && i % POP_SAVE == 0) {
			FileIO::savePopToFile("Population " + std::to_string(i) + ".txt", pop);
		}

		//Save member
		if (i != 0 && i % MEMBER_SAVE == 0) {
			pop.sortMembers();

			std::vector<double> weights = pop.getMember(POP_SIZE - 1).m_network.getWeights();
			FileIO::saveWeightsToFile("Member " + std::to_string(i) + ".txt", weights);
		}
	}
	FileIO::logPrint("Finished Evolution");



	//Save weights and population to file
	pop.sortMembers();

	std::vector<double> weights = pop.getMember(POP_SIZE - 1).m_network.getWeights();
	FileIO::saveWeightsToFile("Member " + std::to_string(GENERATION_COUNT - 1) + ".txt", weights);

	FileIO::savePopToFile("Population " + std::to_string(GENERATION_COUNT - 1) + ".txt", pop);

	pop.startMatch(pop.getMember(POP_SIZE - 1), pop.getMember(POP_SIZE - 2), true);

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