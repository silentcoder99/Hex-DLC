#include "Member.h"

class Match{
    Member& m_player1;
    Member& m_player2;
    double m_invalidMovePenalty;
public:
    Match(Member& player1, Member& player2);
    int getWinner();

    void setInvalidMovePenalty(double penalty);

    Member& getPlayer1();
    Member& getPlayer2();
};

