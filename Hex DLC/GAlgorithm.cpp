#include "GAlgorithm.h"
#include "Game.h"
#include "MyRandom.h"
#include <math.h>
#include <iostream>

Population::Population(int numMembers): m_members(std::vector<Member>()) {
	for (int i = 0; i < numMembers; i++) {
		m_members.push_back(Member());
	}
	m_numMembers = numMembers;
}

Member Population::getMember(int index) {
	return m_members[index];
}

int Population::startMatch(Member player1, Member player2) {
	Board board = Board();

	while (board.getWinner() == 0) {
		std::vector<double> input;
		boardArray rawBoard = board.getBoard();

		//Convert the board to a list
		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				//Player 1
				if (board.getCurrentPlayer() == 1) {
					input.push_back(rawBoard[i][j]);
				}
				//Player 2
				else {
					//Reflect board along the line y = x for player 2
					int value = rawBoard[-j + BOARD_SIZE - 1][-i + BOARD_SIZE - 1];

					//Swap values so they see their moves as '1'
					if (value == 1) {value = 2; }
					else if (value == 2) { value = 1; }

					input.push_back(value);
				}
			}
		}
		//Calculate and perform move

		std::vector<double> output;

		//Player 1
		if (board.getCurrentPlayer() == 1) {
			output = player1.m_network.getOutput(input);

			//Convert from decimal to integer output
			output[0] = floor(output[0] * BOARD_SIZE);
			output[1] = floor(output[1] * BOARD_SIZE);
		}
		//Player 2
		else {
			output = player2.m_network.getOutput(input);

			//Convert from decimal to integer output
			output[0] = floor(output[0] * BOARD_SIZE);
			output[1] = floor(output[1] * BOARD_SIZE);

			//Reflect player 2's move (as they see everything reflected)
			output[0] = -output[1] + BOARD_SIZE - 1;
			output[1] = -output[0] + BOARD_SIZE - 1;
		}

		//If hex is taken, take nearest empty hex
		if (board.getValue(output[0], output[1]) != 0) {
			std::pair<int, int> empty = board.findNearestEmpty(output[0], output[1]);
			output[0] = empty.first;
			output[1] = empty.second;
		}

		board.performMove(output[0], output[1]);

	}
	return board.getWinner();
}

void Population::scoreMembers() {
	//Each player plays all players above them (P2 plays P3, P4, P5, etc.)
	for (int i = 0; i < m_numMembers; i++) {
		for (int j = i + 1; j < m_numMembers; j++) {
			//Award AI's for winning
			if (startMatch(m_members[i], m_members[j]) == 1) {
				m_members[i].m_score++;
			}
			else {
				m_members[j].m_score++;
			}
		}
	}
}

int Population::partitionMembers(int start, int end) {
	int low = start;
	int high = start;

	if (start == end) {
		return -1;
	}

	for (int i = 0; i < end - start; i++) {
		if (m_members[high].m_score > m_members[end].m_score) {
			high++;
		}
		else {
			Member temp = m_members[low];
			m_members[low] = m_members[high];
			m_members[high] = temp;
			low++;
			high++;
		}
	}

	Member temp = m_members[low];
	m_members[low] = m_members[end];
	m_members[end] = temp;

	return low;
}

void Population::sortMembers(int start, int end) {
	//Using the quicksort algorithm
	int pivot = partitionMembers(start, end);

	while (pivot != -1) {
		sortMembers(start, pivot - 1);
		sortMembers(pivot + 1, end);
	}
}

//Member Population::tournamentSelect() {
//	MyRandom rnd = MyRandom();
//	std::vector<Member> theChoosen;
//	
//	for (int i = 0; i < TOURNAMENT_SIZE; i++) {
//		theChoosen.push_back(m_members[rnd.integer(m_numMembers)]);
//	}
//}

Member::Member(): m_network(Network(pow(BOARD_SIZE, 2), LAYER_SIZES, NUM_OUTPUTS)) {
	m_score = 0;
}