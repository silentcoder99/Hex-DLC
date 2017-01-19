#include "TournamentSelection.h"
#include <cmath>
#include "MyRandom.h"

TournamentSelection::TournamentSelection(std::vector<Member>& members, int tournamentSize) 
	: m_members(members),
	m_tournamentSize(tournamentSize){

}


Member& TournamentSelection::select(){

	MyRandom rnd = MyRandom();
	double bestScore = -HUGE_VAL;
	int bestMemberIndex = 0;
	
	for (int i = 0; i < m_tournamentSize; i++) {
		int compeditorMemberIndex = rnd.integer(m_members.size());
		int compeditorMemberScore = m_members[compeditorMemberIndex].m_score;
		
		if (compeditorMemberScore > bestScore) {
			bestMemberIndex = compeditorMemberIndex;
			bestScore = compeditorMemberScore;
		}
	}
	return m_members[bestMemberIndex];
}
