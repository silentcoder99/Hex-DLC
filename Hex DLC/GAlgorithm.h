#pragma once
#include <vector>
#include "Network.h"
#include "SuperArray.hpp"

//Genetic parameters
#define POP_SIZE 10
#define TOURNAMENT_SIZE 2
#define ELITISM_SIZE 1 //Number of top AI's to make it to the next generation
#define MUTATION_RATE 0.2

//Network parameters
#define NUM_INPUTS 121
#define LAYER_SIZES {10}
#define NUM_OUTPUTS 2

//Evolving artifical genomes for dummies:
//1. Create an initial random population
//2. Score each member
//3. Pick members to breed based on score
//4. Breed choosen members
//5. Mutate new population
//6. Repeat steps 2 to 6

struct Member {
	Network m_network;
	int m_score;
	Member();
};

class Population {
	
	int m_numMembers;
	
public:
	Member tournamentSelect();
	void sortMembers(int start = 0, int end = (POP_SIZE - 1));
	std::vector<Member> m_members;

	int startMatch(Member, Member);
	void scoreMembers();
	int partitionMembers(int, int);

	Population(int);
	Member getMember(int);
	void setMember(Member, int);

	static std::pair<Member, Member> crossover(Member, Member);
	static Member mutate(Member);
};
