#include <iostream>
#include <algorithm>
#include "Game.h"

Board::Board() {
	//Set initial board state
	for (auto& column : m_board) {
		column.fill(0);
	}
	m_numTurns = 0;
	m_currentPlayer = 1;
}

Hex::Hex(int x, int y, int value) {
	m_position = { x, y };
	m_value = value;
}

boardArray Board::getBoard() {
	return m_board;
}

bool Board::performMove(int x, int y) {
	if (m_board[x][y] == 0) {
		m_board[x][y] = m_currentPlayer;
		m_currentPlayer = m_currentPlayer == 1 ? 2 : 1; //Toggle the current player between 1 and 2
		m_numTurns++;

		return true;
	}
	else {
		return false;
	}
}

int Board::getValue(int x, int y) {
	return m_board[x][y];
}

// returns distance between points
int distanceHeuristic(int x1, int y1, int x2, int y2) {
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

std::pair<int, int> Board::findNearestEmpty(int x, int y) {
	
	// Initializes closest position to be very far away
	int closestX = 200; 
	int closestY = 200;
	int closestDistance = 200;

	// Iterate board
	for (int prospectiveX = 0; prospectiveX < BOARD_SIZE; prospectiveX++) {
		for (int prospectiveY = 0; prospectiveY < BOARD_SIZE; prospectiveY++) {

			// Is it empty?
			if (m_board[prospectiveX][prospectiveY] == 0) {

				// is it closer than we were?
				if (distanceHeuristic(prospectiveX, prospectiveY, x, y) < closestDistance) {
					
					// Closest so far! save it
					closestX = prospectiveX;
					closestY = prospectiveY;
					closestDistance = distanceHeuristic(prospectiveX, prospectiveY, x, y);
				}
			}
		}
	}
	
	// Return closest tile
	return std::pair<int, int>(closestX, closestY);
}

std::vector<Hex> Board::getNeighbours(int x, int y) {
	std::vector<Hex> neighbours;

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			//Check that surrounding values are valid neighbours
			if (!((x + i < 0) || (x + i > BOARD_SIZE - 1) || (y + j < 0) || (y + j > BOARD_SIZE - 1) || (i == j))) {
				Hex neighbour = Hex(x + i, y + j, m_board[x + i][y + j]);
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

bool Board::connected(int x1, int y1, int x2, int y2, std::vector<std::pair<int, int>>& searched) {
	std::pair<int, int> start = std::pair<int, int>(x1, y1);
	std::pair<int, int> target = std::pair<int, int>(x2, y2);
	int startValue = m_board[x1][y1];

	if (m_board[x1][y1] != m_board[x2][y2]) {
		return false;
	}

	if (start == target) {
		return true;
	}

	searched.push_back(start);

	std::vector<Hex> neighbours = getNeighbours(x1, y1);

	for (auto neighbour : neighbours) {
		if (std::find(searched.begin(), searched.end(), neighbour.m_position) == searched.end() && neighbour.m_value == startValue) {
			if (connected(neighbour.m_position.first, neighbour.m_position.second, x2, y2, searched)) {
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
					if (connected(0, i, BOARD_SIZE - 1, j)) {
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
					if (connected(i, 0, j, BOARD_SIZE - 1)) {
						return 2;
					}
				}
			}
		}
	}

	return 0;
}

void Board::print() {
	for (int row = 0; row < BOARD_SIZE; row++) {
		for (int i = 0; i < row; i++) {
			std::cout << " ";
		}
		for (auto column : m_board) {
				std::cout << column[row] << " ";
		}
		std::cout << "\n";
	}
}