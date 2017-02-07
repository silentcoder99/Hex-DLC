#pragma once

#include <time.h>
#include "genetics/Population.h"
#include <boost/thread.hpp>

// Thread safe HexDLC code
class HexDLC {
	boost::mutex m_populationMutex;
	Population m_population;
	bool m_DLCRunning = true;

	time_t m_runTime = 0;

public:
	HexDLC();
	void run(); // Run this on different thread
	void stop();
	Member getChampion();
	unsigned long int getGenerationCount();
	void setGenerationCount(unsigned long int generationCount);

	Array<int> getLayerSizes();
	Population getPopulation();

	double getRunningTime();

	void setPopulation(Population pop);

	std::string getState();
	std::string getMatch();

};
