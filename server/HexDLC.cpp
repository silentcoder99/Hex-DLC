#include "HexDLC.h"

#include <math.h>
#include "MyRandom.h"
#include "Network.h"
#include "Game.h"
#include "FileIO.h"
#include <iostream>
#include <sstream>

#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>


HexDLC::HexDLC() :mPopulation(true)
{
}

void HexDLC::run() {

	time_t initialTime;
	bool benchmarkRunning = false;

	while (mDLCRunning) {
		mPopulation = Population::evolve(mPopulation);

		if (mChampionRequested) {
			mPopulation.sortMembers();
			mChampion = new Member(mPopulation.getMember(POP_SIZE - 1));
			mChampionRequested = false;
		}

		if (mPopulationRequested) {
			mPopulationPointer = new Population(mPopulation);
			mPopulationRequested = false;
		}

		mGenerationCount++;
		if (mNewPopulation != nullptr) {
			mPopulation = *mNewPopulation;
			delete mNewPopulation;
			mNewPopulation = nullptr;

			mGenerationCount = 0;
		}

		if (benchmarkRunning) {
			mRunTime = clock() - initialTime;
			benchmarkRunning = false;
			mTimeRequested = false;
		}

		if (mTimeRequested) {
			initialTime = clock();
			benchmarkRunning = true;
		}
	}
}

void HexDLC::stop()
{
	mDLCRunning = false;
}

Member HexDLC::getChampion()
{
	mChampionRequested = true;
	while (mChampion == nullptr) {
		boost::this_thread::sleep(boost::posix_time::milliseconds(10));
	}
	Member champion = *mChampion;
	delete mChampion;
	mChampion = nullptr;
	return champion;
}

unsigned long int HexDLC::getGenerationCount() {
	return mGenerationCount;
}

void HexDLC::setGenerationCount(unsigned long int generationCount)
{
	mGenerationCount = generationCount;
}

std::vector<int> HexDLC::getLayerSizes() {
	return LAYER_SIZES;
}

Population HexDLC::getPopulation()
{
	mPopulationRequested = true;
	while (mPopulationPointer == nullptr) {
		boost::this_thread::sleep(boost::posix_time::milliseconds(10));
	}
	Population pop = *mPopulationPointer;
	delete mPopulationPointer;
	mPopulationPointer = nullptr;
	return pop;
}

double HexDLC::getRunningTime()
{
	mTimeRequested = true;
	while (mRunTime == 0) {
		boost::this_thread::sleep(boost::posix_time::milliseconds(10));
	}
	double runningTime = (float)mRunTime / CLOCKS_PER_SEC;

	mRunTime = 0;
	return runningTime;
}

void HexDLC::setPopulation(Population pop)
{
	mNewPopulation = new Population(pop);
}

std::string HexDLC::getState()
{
	return mPopulation.save();
}

std::string HexDLC::getMatch()
{
	Member champion = getChampion();
	std::stringstream ss;
	mPopulation.startMatch(champion, champion, &ss);
	return ss.str();
}
