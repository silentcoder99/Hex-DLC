#include "SelectionAlgorithm.h"
#include <vector>

class TournamentSelection : public SelectionAlgorithm{
	std::vector<Member>& m_members;
	const int m_tournamentSize;
public:
	TournamentSelection(std::vector<Member>& members, int tournamentSize);
	
	virtual Member& select();	
};
