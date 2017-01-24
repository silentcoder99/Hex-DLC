#include "HexDLC.h"

#include <math.h>
#include "MyRandom.h"
#include "Game.h"
#include "FileIO.h"
#include <iostream>
#include <sstream>
#include "Logger.h"

#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>


HexDLC::HexDLC()
{
	m_population.populate();
}

void HexDLC::run() {

	while (m_DLCRunning) {

		clock_t initialTime = clock();
		// The real process
		m_populationMutex.lock();

		m_population.evolve();

        std::string message = "Generation Number " + std::to_string(m_population.getGenerationCount()) + " Evolved";
        Logger::getInstance()->logInfo(message, 1);
		m_populationMutex.unlock();

		m_runTime = clock() - initialTime;
	}
}
void HexDLC::stop()
{
	m_DLCRunning = false;
}

Member HexDLC::getChampion()
{
	boost::lock_guard<boost::mutex> lock(m_populationMutex);
	return m_population.getChampion();
}

unsigned long int HexDLC::getGenerationCount() {
	return m_population.getGenerationCount();
}

void HexDLC::setGenerationCount(unsigned long int generationCount)
{
	m_population.setGenerationCount(generationCount);
}

Array<int> HexDLC::getLayerSizes() {
	return m_population.getLayerSizes();
}

Population HexDLC::getPopulation()
{
	boost::lock_guard<boost::mutex> lock(m_populationMutex);
	return m_population;
}

double HexDLC::getRunningTime()
{
	return m_runTime;
}

void HexDLC::setPopulation(Population pop)
{
	boost::lock_guard<boost::mutex> lock(m_populationMutex);
	m_population = pop;
}

std::string HexDLC::getState()
{
	return m_population.save();
}

std::string HexDLC::getMatch()
{
	Member champion = getChampion();
	std::stringstream ss;
	m_population.startMatch(champion, champion, &ss);
	return ss.str();
}
