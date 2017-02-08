#pragma once
#include <vector>
#include "Member.h"
#include "util/FastArray.h"
#include <pugixml.hpp>

//Genetic parameters
#define GENERATION_COUNT 50
#define POP_SIZE 50
#define TOURNAMENT_SIZE 2
#define ELITISM_SIZE 1 //Number of top AI's to make it to the next generation
#define MUTATION_RATE 0.2 // Interpreted as a percentage of weights changed per generation
#define WIN_REWARD 1
#define INVALID_MOVE_PENALTY 0

//Network parameters
#define LAYER_SIZES {50, 20}

#define NUM_THREADS 8

//Evolving artifical genomes for dummies:
//1. Create an initial random population
//2. Score each member
//3. Pick members to breed based on score
//4. Breed choosen members
//5. Mutate new population
//6. Repeat steps 2 to 6

class Population {

	unsigned long m_generationCount = 0;
	int m_tournamentSize = TOURNAMENT_SIZE;
	int m_elitismSize = ELITISM_SIZE;
	double m_mutationRate = MUTATION_RATE;
	double m_winReward = WIN_REWARD;
	double m_invalidMovePenalty = INVALID_MOVE_PENALTY;
	Array<int> m_layerSizes = LAYER_SIZES;

	std::vector<Member> m_members;

	int partitionMembers(int, int);

	pugi::xml_node saveMember(Member);

public:
	int startMatch(Member&, Member&, std::ostream* = nullptr);
	void sortMembers(int start = 0, int end = (POP_SIZE - 1));
	void scoreMembers();
	Population();
	void populate(int numNewMembers = POP_SIZE);
	Member& getMember(int);
	void setMember(Member, int);
	void addMember(Member);

	Member getChampion();

	// Returns a string representation of the population
	std::string save();
	void load(std::string package);

	unsigned long getGenerationCount();
	void setGenerationCount(unsigned long generationCount);

	Array<int> getLayerSizes();

	static std::pair<Member, Member> crossover(Member, Member);
	void evolve();
};
