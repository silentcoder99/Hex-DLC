#include "Match.h"
#include <Game.h>

Match::Match(Member& player1, Member& player2):
    m_player1(player1),
    m_player2(player2){
}


int Match::getWinner(){
   Board board = Board();

	while (board.getWinner() == 0) {
		Array<double> input(BOARD_SIZE * BOARD_SIZE);
		boardArray rawBoard = board.getBoard();

		//Convert the board to a list
		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				//Player 1
				if (board.getCurrentPlayer() == 1) {
					if (rawBoard[i][j] == 0) {
						input[i * 11 + j] = 0;
					}
					else if (rawBoard[i][j] == 1) {
						input[i * 11 + j] = 1;
					}
					else if (rawBoard[i][j] == 2) {
						input[i * 11 + j] = -1;
					}
				}
				//Player 2
				else {
					//Reflect board along the line y = x for player 2
					int value = rawBoard[-j + BOARD_SIZE - 1][-i + BOARD_SIZE - 1];

					//Swap values so they see their moves as '1'
					if (value == 1) { value = -1; }
					else if (value == 2) { value = 1; }

					input[i * 11 + j] = value;
				}
			}
		}

		//Calculate and perform move

		Array<double> output(NUM_OUTPUTS);

		if (board.getCurrentPlayer() == 1) {
			// Get Output
			output = m_player1.getNetwork().getOutput(input);

			//Convert from decimal to integer output
			output[0] = floor(output[0] * BOARD_SIZE);
			output[1] = floor(output[1] * BOARD_SIZE);
		}
		else if (board.getCurrentPlayer() == 2) {
			// Get Output
			output = m_player2.getNetwork().getOutput(input);

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

			// If we are printing, don't apply penalties, blank match
            //Penalize player for performing an illegal move
            if (board.getCurrentPlayer() == 1) {
                m_player1.takeScore(m_invalidMovePenalty);
            }
            else if (board.getCurrentPlayer() == 2) {
                m_player2.takeScore(m_invalidMovePenalty);
            }
		}

		board.performMove(chosenPosition);

	}
	return board.getWinner();
  
}

Member& Match::getPlayer1(){
    return m_player1;
}

Member& Match::getPlayer2(){
    return m_player2;
}

void Match::setInvalidMovePenalty(double penalty){
    m_invalidMovePenalty = penalty;
}
