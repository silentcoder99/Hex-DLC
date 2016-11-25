#include "GAlgorithm.h"
#include "Game.h"
#include "MyRandom.h"
#include <math.h>
#include <iostream>

Population::Population(bool init): m_members(std::vector<Member>()) {
	if (init) {
		for (int i = 0; i < POP_SIZE; i++) {
			m_members.push_back(Member());
		}
		m_numMembers = POP_SIZE;
	}
	else {
		m_numMembers = 0;
	}
}

Member Population::getMember(int index) {
	return m_members[index];
}

void Population::setMember(Member member, int index) {
	m_members[index] = member;
}

void Population::addMember(Member member) {
	m_members.push_back(member);
	m_numMembers = m_members.size();
}

int Population::startMatch(Member& player1, Member& player2, bool log = false) {
	Board board = Board();

	while (board.getWinner() == 0) {
		Array<double> input(BOARD_SIZE * BOARD_SIZE);
		boardArray rawBoard = board.getBoard();

		//Convert the board to a list
		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				//Player 1
				if (board.getCurrentPlayer() == 1) {
					input[i * 11 + j] = rawBoard[i][j];
				}
				//Player 2
				else {
					//Reflect board along the line y = x for player 2
					int value = rawBoard[-j + BOARD_SIZE - 1][-i + BOARD_SIZE - 1];

					//Swap values so they see their moves as '1'
					if (value == 1) { value = 2; }
					else if (value == 2) { value = 1; }

					input[i * 11 + j] = value;
				}
			}
		}

		//Calculate and perform move

		Array<double> output(NUM_OUTPUTS);

		if (board.getCurrentPlayer() == 1) {
			// Get Output
			output = player1.m_network.getOutput(input);

			//Convert from decimal to integer output
			output[0] = floor(output[0] * BOARD_SIZE);
			output[1] = floor(output[1] * BOARD_SIZE);
		}
		else if (board.getCurrentPlayer() == 2) {
			// Get Output
			output = player2.m_network.getOutput(input);

			//Convert from decimal to integer output
			output[0] = floor(output[0] * BOARD_SIZE);
			output[1] = floor(output[1] * BOARD_SIZE);

			//Reflect player 2's move (as they see everything reflected)
			output[0] = -output[1] + BOARD_SIZE - 1;
			output[1] = -output[0] + BOARD_SIZE - 1;
		}

		Vec2 chosenPosition = Vec2((int)output[0], (int)output[1]);

		//If hex is taken, take nearest empty hex
		if (board.getValue(chosenPosition) != 0) {
			Vec2 emptyPos = board.findNearestEmpty(chosenPosition);
			chosenPosition = emptyPos;

			//Penalize player for performing an illegal move
			if (board.getCurrentPlayer() == 1) {
				player1.m_score -= INVALID_MOVE_PENALTY;
			}
			else if (board.getCurrentPlayer() == 2) {
				player2.m_score -= INVALID_MOVE_PENALTY;
			}
		}

		board.performMove(chosenPosition);

		if (log) {
			board.print();
		}

	}
	return board.getWinner();
}

void Population::scoreMembers() {
	//Each player plays all players above them (P2 plays P3, P4, P5, etc.)
	for (int i = 0; i < m_numMembers; i++) {
		for (int j = i + 1; j < m_numMembers; j++) {
			//Award AI's for winning
			if (startMatch(m_members[i], m_members[j]) == 1) {
				m_members[i].m_score += WIN_REWARD;
			}
			else {
				m_members[j].m_score += WIN_REWARD;
			}
		}
	}
}

int Population::partitionMembers(int start, int end) {
	int low = start;
	double pivot = m_members[end].m_score;

	for (int i = start; i < end; i++) {
		if (m_members[i].m_score <= pivot) {
			Member temp = m_members[low];
			m_members[low] = m_members[i];
			m_members[i] = temp;
			low++;
		}
	}

	Member temp = m_members[low];
	m_members[low] = m_members[end];
	m_members[end] = temp;

	return low;
}

void Population::sortMembers(int start, int end) {
	//Using the quicksort algorithm
	if (start < end) {
		int pivot = partitionMembers(start, end);
		sortMembers(start, pivot - 1);
		sortMembers(pivot + 1, end);
	}
}

Member Population::tournamentSelect() {
	MyRandom rnd = MyRandom();
	double bestScore = 0;
	Member bestMember;
	
	for (int i = 0; i < TOURNAMENT_SIZE; i++) {
		Member choosen = m_members[rnd.integer(m_numMembers)];
		
		if (choosen.m_score > bestScore) {
			bestMember = choosen;
		}
	}
	return bestMember;
}

std::pair<Member, Member> Population::crossover(Member member1, Member member2) {
	//Creates 2 new children using randomly selected weights from each parent
	MyRandom rnd = MyRandom();

	Array<double> firstWeights = member1.m_network.getWeights();
	Array<double> secondWeights = member2.m_network.getWeights();

	for (unsigned int i = 0; i < firstWeights.size(); i++) {
		if (rnd.integer(2) == 1) {
			double temp = secondWeights[i];
			secondWeights[i] = firstWeights[i];
			firstWeights[i] = temp;
		}
	}

	Member child1 = Member();
	Member child2 = Member();
	child1.m_network.setWeights(firstWeights);
	child2.m_network.setWeights(secondWeights);

	return { child1, child2 };
}

Member::Member(): m_network(Network(NUM_INPUTS, LAYER_SIZES, NUM_OUTPUTS)) {
	m_score = 0;
}

Member Population::mutate(Member member) {
	MyRandom rnd = MyRandom();

	Array<double> weights = member.m_network.getWeights();

	for (unsigned int i = 0; i < weights.size(); i++) {
		if (rnd.real(0, 1) < MUTATION_RATE) {
			weights[i] = rnd.real(-1, 1);
		}
	}

	member.m_network.setWeights(weights);
	return member;
}

Population Population::evolve(Population pop) {

	pop.scoreMembers();
	pop.sortMembers();

	Population newPop = Population(false);

	//Add top members from previous generation
	for (int i = 0; i < ELITISM_SIZE; i++) {
		Member elite = pop.getMember(POP_SIZE - i - 1);
		elite.m_score = 0;
		newPop.addMember(elite);
	}

	//Add children until pop size is reached
	while (newPop.m_numMembers < POP_SIZE) {
		Member parent1 = pop.tournamentSelect();
		Member parent2 = pop.tournamentSelect();
		std::pair<Member, Member> children = Population::crossover(parent1, parent2);
		newPop.addMember(children.first);
		if (newPop.m_numMembers < POP_SIZE) {
			newPop.addMember(children.second);
		}
	}

	//Mutate new members
	for (int i = 0; i < POP_SIZE; i++) {
		Member mutant = Population::mutate(newPop.getMember(i));
		newPop.setMember(mutant, i);
	}
	
	return newPop;
}
