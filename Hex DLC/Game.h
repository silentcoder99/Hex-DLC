#pragma once
#include <array>
#include <vector>
#include "Vec2.hpp"

#define BOARD_SIZE 11

typedef std::array<std::array<int, BOARD_SIZE>, BOARD_SIZE> boardArray;

struct Hex {
	Hex(Vec2 pos, int);
	Vec2 m_position;
	int m_value;
};

class Board {
	boardArray m_board;
	int m_numTurns;
	int m_currentPlayer;
	std::vector<Hex> getNeighbours(Vec2 position);
	bool connected(Vec2 start, Vec2 target, std::vector<Vec2>& = std::vector<Vec2>());
public:
	Board();
	Vec2 findNearestEmpty(Vec2 position);
	boardArray getBoard();
	bool performMove(Vec2 position);
	int getValue(Vec2 position);
	void setValue(Vec2 position, int value);

	int getNumTurns();
	int getCurrentPlayer();
	int getWinner();
	void print();
};