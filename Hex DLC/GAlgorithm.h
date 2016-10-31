#pragma once
#include <vector>
#include "Network.h"

//Genetic parameters
#define POP_SIZE 10
#define TOURNAMENT_SIZE 20
#define ELITISM true

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
	Member tournamentSelect();
	
public:
	void sortMembers(int, int);
	std::vector<Member> m_members;

	int startMatch(Member, Member);
	void scoreMembers();
	int partitionMembers(int, int);

	Population(int);
	Member getMember(int);
};
