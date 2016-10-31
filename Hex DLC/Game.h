#pragma once
#include <array>
#include <vector>

#define BOARD_SIZE 11

typedef std::array<std::array<int, BOARD_SIZE>, BOARD_SIZE> boardArray;

struct Hex {
	Hex(int, int, int);
	std::pair<int, int> m_position;
	int m_value;
};

class Board {
	boardArray m_board;
	int m_numTurns;
	int m_currentPlayer;
	std::vector<Hex> getNeighbours(int, int);
	bool connected(int, int, int, int, std::vector<std::pair<int, int>>& = std::vector<std::pair<int, int>>());
public:
	Board();
	std::pair<int, int> findNearestEmpty(int, int);
	boardArray getBoard();
	bool performMove(int, int);
	int getValue(int, int);
	int getNumTurns();
	int getCurrentPlayer();
	int getWinner();
	void print();
};