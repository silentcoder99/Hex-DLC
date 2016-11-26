#include <iostream>
#include "Server.h"
#include "HexDLC.h"

//Log Parameters
#define LOG true
#define MEMBER_SAVE 10 //How frequently the best member is saved
#define POP_SAVE 10 //How frequently the population is saved

int main() {
#ifdef PROFILING
	HexDLC hex;
	hex.run();
#else
	DLCServer server;
	server.start();
#endif

	//
	////Save weights and population to file
	//pop.scoreMembers();
	//pop.sortMembers();

	//std::vector<double> weights = pop.getMember(POP_SIZE - 1).m_network.getWeights();
	//FileIO::saveWeightsToFile("Member " + std::to_string(GENERATION_COUNT - 1) + ".txt", weights);

	//FileIO::savePopToFile("Population " + std::to_string(GENERATION_COUNT - 1) + ".txt", pop)
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