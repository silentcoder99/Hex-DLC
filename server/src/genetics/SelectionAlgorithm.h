#include "Member.h"

/*
 * SelectionAlgorith Class
 * An abstract class specifying a way of selecting members from a population
 *
 * The current concrete classes extending this are:
 *  - TournamentSelection from TournamentSelection.h
 *
 * Example:
 * SelectionAlgorithm* algorithm = new TournamentSelection([members], [tournament_size])
 */

class SelectionAlgorithm{
public:
    virtual ~SelectionAlgorithm(){};
	// Returns the index of the member selected
	virtual Member& select() = 0;
};
