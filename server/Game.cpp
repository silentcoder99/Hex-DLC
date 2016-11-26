#include <iostream>
#include <algorithm>
#include "Game.h"
#include "FileIO.h"

Board::Board() {
	//Set initial board state
	for (auto& column : m_board) {
		column.fill(0);
	}
	m_numTurns = 0;
	m_currentPlayer = 1;
}

Hex::Hex(Vec2 pos, int value) {
	m_position = pos;
	m_value = value;
}

boardArray Board::getBoard() {
	return m_board;
}

bool Board::performMove(Vec2 pos) {
	if (getValue(pos) == 0) {
		setValue(pos, m_currentPlayer);
		m_currentPlayer = m_currentPlayer == 1 ? 2 : 1; //Toggle the current player between 1 and 2
		m_numTurns++;

		return true;
	}
	else {
		return false;
	}
}

int Board::getValue(Vec2 pos) {
	return m_board[pos.x][pos.y];
}

void Board::setValue(Vec2 pos, int value) {
	m_board[pos.x][pos.y] = value;
}

// returns distance between points
double distanceHeuristic(Vec2 firstPos, Vec2 secondPos) {
	return firstPos.distance(secondPos);
}

Vec2 Board::findNearestEmpty(Vec2 position) {
	
	// Initializes closest position to be very far away
	Vec2 closestPos(200, 200);

	double closestDistance = 200;

	// Iterate board
	for (int prospectiveX = 0; prospectiveX < BOARD_SIZE; prospectiveX++) {
		for (int prospectiveY = 0; prospectiveY < BOARD_SIZE; prospectiveY++) {
			
			Vec2 prospecivePosition = Vec2(prospectiveX, prospectiveY);

			// Is it empty?
			if (getValue(prospecivePosition) == 0) {

				double distance = distanceHeuristic(prospecivePosition, position);

				// is it closer than we were?
				if (distance < closestDistance) {
					
					// Closest so far! save it
					closestPos = prospecivePosition;
					closestDistance = distance;
				}
			}
		}
	}

	// Return closest tile
	return closestPos;
}

int Board::getNumTurns() {
	return m_numTurns;
}

int Board::getCurrentPlayer() {
	return m_currentPlayer;
}

bool Board::connectedToRight(Vec2 start, bool searched[BOARD_SIZE][BOARD_SIZE]) {
	int startValue = getValue(start);

	static const Vec2 neighbours[] = {
		Vec2(1, 0),
		Vec2(1, -1),
		Vec2(0, 1),
		Vec2(0, -1),
		Vec2(-1, 0),
		Vec2(-1, 1)
	};

	if (start.x == BOARD_SIZE - 1) {
		return true;
	}

	searched[start.x][start.y] = true;

	for (auto neighbour : neighbours) {
		Vec2 boardNeighbor = neighbour + start;

		bool outsideOfBoard = boardNeighbor.x < 0 || boardNeighbor.x >= BOARD_SIZE || boardNeighbor.y < 0 || boardNeighbor.y >= BOARD_SIZE;
		if (outsideOfBoard) {
			continue;
		}

		if (!searched[boardNeighbor.x][boardNeighbor.y] && getValue(boardNeighbor) == startValue) {
			if (connectedToRight(boardNeighbor, searched)) {
				return true;
			}
		}
	}
	return false;
}

bool Board::connectedToBottom(Vec2 start, bool searched[BOARD_SIZE][BOARD_SIZE]) {
	int startValue = getValue(start);

	static const Vec2 neighbours[] = {
		Vec2(-1, 1),
		Vec2(0, 1),
		Vec2(1, 0),
		Vec2(-1, 0),
		Vec2(1, -1),
		Vec2(0, -1),
	};

	if (start.y == BOARD_SIZE - 1) {
		return true;
	}

	searched[start.x][start.y] = true;

	for (auto neighbour : neighbours) {
		Vec2 boardNeighbor = neighbour + start;

		bool outsideOfBoard = boardNeighbor.x < 0 || boardNeighbor.x >= BOARD_SIZE || boardNeighbor.y < 0 || boardNeighbor.y >= BOARD_SIZE;
		if (outsideOfBoard) {
			continue;
		}

		if (!searched[boardNeighbor.x][boardNeighbor.y] && getValue(boardNeighbor) == startValue) {
			if (connectedToBottom(boardNeighbor, searched)) {
				return true;
			}
		}
	}
	return false;
}


int Board::getWinner() {
	bool checkedPlayer1[BOARD_SIZE][BOARD_SIZE] = { false };

	//Test for player 1 victory
	for (int i = 0; i < BOARD_SIZE; i++) {
		if (m_board[0][i] == 1 && !checkedPlayer1[0][i]) {
			if (connectedToRight(Vec2(0, i), checkedPlayer1)) {
				return 1;
			}
		}
	}

	bool checkedPlayer2[BOARD_SIZE][BOARD_SIZE] = { false };

	//Test for player 2 victory
	for (int i = 0; i < BOARD_SIZE; i++) {
		if (m_board[i][0] == 2 && !checkedPlayer2[i][0]) {
			if (connectedToBottom(Vec2(i, 0), checkedPlayer2)) {
				return 2;
			}
		}
	}

	return 0;
}

void Board::print() {
	std::string str;
	str += "\n";
	for (int row = 0; row < BOARD_SIZE; row++) {
		for (int i = 0; i < row; i++) {
			str += " ";
		}
		for (auto column : m_board) {
			str += std::to_string(column[row]) + " ";
		}
		str += "\n";
	}
	str += "\n";
	FileIO::logPrint(str);
}