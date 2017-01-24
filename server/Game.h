#pragma once
#include <array>
#include <vector>
#include "util/Vec2.hpp"
#include <list>
#include <unordered_set>

#define BOARD_SIZE 11

typedef std::array<std::array<int, BOARD_SIZE>, BOARD_SIZE> boardArray;

struct Hex {
	Hex(Vec2 pos, int);
	bool operator<(Hex other) const{
		return m_position.x + m_position.y * 11 < other.m_position.x + other.m_position.y * 11;
	}
	Vec2 m_position;
	int m_value;
};

class Board {
	boardArray m_board;
	int m_numTurns;
	int m_currentPlayer;
	bool connectedToRight(Vec2 start, bool checked[BOARD_SIZE][BOARD_SIZE]);
	bool connectedToBottom(Vec2 start, bool checked[BOARD_SIZE][BOARD_SIZE]);
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
	std::string toString();
};
