#pragma once
#include <vector>
#include "Network.h"
#include "SuperArray.hpp"

//Genetic parameters
#define GENERATION_COUNT 50
#define POP_SIZE 50
#define TOURNAMENT_SIZE 2
#define ELITISM_SIZE 1 //Number of top AI's to make it to the next generation
#define MUTATION_RATE 0.2
#define WIN_REWARD 1
#define INVALID_MOVE_PENALTY 0

//Network parameters
#define NUM_INPUTS 121
#define LAYER_SIZES {50, 20}
#define NUM_OUTPUTS 2

#define NUM_THREADS 8

//Evolving artifical genomes for dummies:
//1. Create an initial random population
//2. Score each member
//3. Pick members to breed based on score
//4. Breed choosen members
//5. Mutate new population
//6. Repeat steps 2 to 6

struct Member {
	Network m_network;
	double m_score;
	Member();
};

class Population {
	
	int m_numMembers;
	Member tournamentSelect();
	std::vector<Member> m_members;
	
	int partitionMembers(int, int);

public:
	int startMatch(Member&, Member&, bool log);
	void sortMembers(int start = 0, int end = (POP_SIZE - 1));
	void scoreMembers();
	Population(bool init);
	Member getMember(int);
	void setMember(Member, int);
	void addMember(Member);

	static std::pair<Member, Member> crossover(Member, Member);
	static Member mutate(Member);
	static Population evolve(Population);
};
