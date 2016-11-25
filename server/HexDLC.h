#pragma once

#include "GAlgorithm.h"

// Thread safe HexDLC code
class HexDLC {
public:
	HexDLC();
	void run(); // Run this on different thread
	void stop();
	Member getChampion();
private:
	Population mPopulation;
	bool mDLCRunning = true;

	bool mChampionRequested = false;
	Member* mChampion = nullptr;
};