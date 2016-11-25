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

std::list<Hex> Board::getNeighbours(Vec2 pos) {
	std::list<Hex> neighbours;

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			//Check that surrounding values are valid neighbours
			if (!((pos.x + i < 0) || (pos.x + i > BOARD_SIZE - 1) || (pos.y + j < 0) || (pos.y + j > BOARD_SIZE - 1) || (i == j))) {
				Hex neighbour = Hex(Vec2(pos.x + i, pos.y + j), m_board[pos.x + i][pos.y + j]);
				neighbours.push_back(neighbour);
			}
		}
	}
	return neighbours;
}

int Board::getNumTurns() {
	return m_numTurns;
}

int Board::getCurrentPlayer() {
	return m_currentPlayer;
}

bool Board::connected(Vec2 start, Vec2 target, std::vector<Vec2>& searched) {
	int startValue = getValue(start);

	if (getValue(start) != getValue(target)) {
		return false;
	}

	if (start == target) {
		return true;
	}

	searched.push_back(start);

	std::list<Hex> neighbours = getNeighbours(start);

	for (auto neighbour : neighbours) {
		if (std::find(searched.begin(), searched.end(), neighbour.m_position) == searched.end() && neighbour.m_value == startValue) {
			if (connected(neighbour.m_position, target, searched)) {
				return true;
			}
		}
	}

	return false;
}

int Board::getWinner() {
	//Test for player 1 victory
	for (int i = 0; i < BOARD_SIZE; i++) {
		if (m_board[0][i] == 1) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				if (m_board[BOARD_SIZE - 1][j] == 1) {
					if (connected(Vec2(0, i), Vec2(BOARD_SIZE - 1, j))) {
						return 1;
					}
				}
			}
		}
	}

	//Test for player 2 victory
	for (int i = 0; i < BOARD_SIZE; i++) {
		if (m_board[i][0] == 2) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				if (m_board[j][BOARD_SIZE - 1] == 2) {
					if (connected(Vec2(i, 0), Vec2(j, BOARD_SIZE - 1))) {
						return 2;
					}
				}
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