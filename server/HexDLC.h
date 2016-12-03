#pragma once

#include <time.h>
#include "GAlgorithm.h"

// Thread safe HexDLC code
class HexDLC {
public:
	HexDLC();
	void run(); // Run this on different thread
	void stop();
	Member getChampion();
	unsigned long int getGenerationCount();
	void setGenerationCount(unsigned long int generationCount);

	std::vector<int> getLayerSizes();
	Population getPopulation();

	double getRunningTime();

	void setPopulation(Population pop);

	std::string getState();
private:
	Population mPopulation;
	bool mDLCRunning = true;

	bool mChampionRequested = false;
	Member* mChampion = nullptr;

	bool mPopulationRequested = false;
	Population* mPopulationPointer = nullptr;

	Population* mNewPopulation = nullptr;

	bool mTimeRequested = false;
	time_t mRunTime = 0;

	unsigned long int mGenerationCount = 0;
};
