#include <iostream>
#include <math.h>
#include "MyRandom.h"
#include "Network.h"
#include "Game.h"
#include "GAlgorithm.h"

#include "FileIO.h"

int main() {

	Population pop = Population(POP_SIZE);
	std::vector<double> weights;

	weights = pop.getMember(0).m_network.getWeights();
	
	for (auto weight : weights) {
		std::cout << weight << ", ";
	}
	std::cout << "\n";

	Member mutant = Population::mutate(pop.getMember(0));
	pop.setMember(mutant, 0);

	weights = pop.getMember(0).m_network.getWeights();

	for (auto weight : weights) {
		std::cout << weight << ", ";
	}


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