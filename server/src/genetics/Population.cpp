#include "Population.h"
#include "Match.h"
#include "MyRandom.h"
#include <math.h>
#include <iostream>
#include <sstream>
#include "WorkerThread.h"
#include "TournamentSelection.h"

#include "util/FileIO.h"

#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <queue>


// Tag names
#define POPULATION_TAG "population"
#define POPULATION_SIZE_ATTR "populationSize"
#define TOURNAMENT_SIZE_ATTR "tournamentSize"
#define ELITISM_SIZE_ATTR "elitismSize"
#define MUTATION_RATE_ATTR "mutationRate"
#define WIN_REWARD_ATTR "winReward"
#define INVALID_MOVE_PENALTY_ATTR "invalidMovePenalty"
#define LAYER_SIZES_TAG "layerSizes"
#define LAYER_TAG "layer"
#define MEMBER_COLLECTION_TAG "members"
#define MEMBER_ELEMENT_TAG "member"

Population::Population() {
	
}

void Population::populate(int numNewMembers) {
	for (int i = 0; i < numNewMembers; i++) {
		m_members.push_back(Member(m_layerSizes));
	}
}

Member& Population::getMember(int index) {
	return m_members[index];
}

void Population::setMember(Member member, int index) {
	m_members[index] = member;
}

void Population::addMember(Member member) {
	m_members.push_back(member);
}

pugi::xml_node Population::saveMember(Member member) {
	Array<double> weights = member.getNetwork().getWeights();
	std::string weightsString = FileIO::doubleArrayToString(weights);
	pugi::xml_node node;
	node.set_name(MEMBER_ELEMENT_TAG);
	node.append_child(pugi::node_pcdata).set_value(weightsString.c_str());
	return node;
}

std::string Population::save()
{
	using namespace pugi;

	xml_document doc;
	xml_node populationNode = doc.append_child(POPULATION_TAG);

	populationNode.append_attribute(POPULATION_SIZE_ATTR).set_value(m_members.size());
	populationNode.append_attribute(TOURNAMENT_SIZE_ATTR).set_value(m_tournamentSize);
	populationNode.append_attribute(ELITISM_SIZE_ATTR).set_value(m_elitismSize);
	populationNode.append_attribute(MUTATION_RATE_ATTR).set_value(m_mutationRate);
	populationNode.append_attribute(WIN_REWARD_ATTR).set_value(m_winReward);
	populationNode.append_attribute(INVALID_MOVE_PENALTY_ATTR).set_value(m_invalidMovePenalty);

	xml_node layerSizesNode = populationNode.append_child(LAYER_SIZES_TAG);

	for (int layerIndex = 0; layerIndex < m_layerSizes.size(); layerIndex++) {
		layerSizesNode.append_child(LAYER_TAG).append_child(node_pcdata).set_value(std::to_string(m_layerSizes[layerIndex]).c_str());
	}
	

	xml_node membersNode = populationNode.append_child(MEMBER_COLLECTION_TAG);

	//Save members
	for (int i = 0; i < POP_SIZE; i++) {
		membersNode.append_move(saveMember(getMember(i)));
	}

	std::stringstream ss;
	doc.save(ss);

	return ss.str();

}

void Population::load(std::string package) {
	using namespace pugi;
	xml_document doc;
	doc.load_string(package.c_str());

	xml_node populationNode = doc.child(POPULATION_TAG);

	m_tournamentSize = populationNode.attribute(TOURNAMENT_SIZE_ATTR).as_int();
	m_elitismSize = populationNode.attribute(ELITISM_SIZE_ATTR).as_int();
	m_mutationRate = populationNode.attribute(MUTATION_RATE_ATTR).as_double();
	m_winReward = populationNode.attribute(WIN_REWARD_ATTR).as_double();
	m_invalidMovePenalty = populationNode.attribute(INVALID_MOVE_PENALTY_ATTR).as_double();

	xml_node layerSizesNode = populationNode.child(LAYER_SIZES_TAG);
	int layerCount = 0;
	
	for (xml_node layerNode : layerSizesNode.children()) {
		layerCount++;
	}

	m_layerSizes = Array<int>(layerCount);

	int layerIndex = 0;
	for (xml_node layerNode : layerSizesNode.children()) {
		m_layerSizes[layerIndex] = layerNode.text().as_int();
		layerIndex++;
	}
	m_members.clear();
	xml_node membersNode = populationNode.child(MEMBER_COLLECTION_TAG);

	for (xml_node memberNode : membersNode) {
		Member newMember = Member(m_layerSizes);
		newMember.getNetwork().setWeights(FileIO::stringToDoubleArray(memberNode.text().as_string()));
		addMember(newMember);
	}

}

void Population::scoreMembers() {

	ThreadSafeStack<std::function<void()>> taskStack;

	//Each player plays all players above them (P2 plays P3, P4, P5, etc.)
	for (unsigned int i = 0; i < m_members.size(); i++) {
		for (unsigned int j = i + 1; j < m_members.size(); j++) {
			//Award AI's for winning
			taskStack.push([this, i, j]() {
                Match match(m_members[i], m_members[j]);
                match.setInvalidMovePenalty(m_invalidMovePenalty);
				if (match.getWinner() == 1) {
					m_members[i].addScore(m_winReward);
				}
				else {
					m_members[j].addScore(m_winReward);
				}
			});
		}
	}

	// Get the threads to it!
	std::queue<WorkerThread*> threadStack;
	for (int i = 0; i < NUM_THREADS; i++) {
		threadStack.push(new WorkerThread(taskStack));
	}

	// Destroy threads after they are done
	while (!threadStack.empty()) {

		// Wait till done
		threadStack.front()->join();

		// Destroy thread
		delete threadStack.front();
		threadStack.pop();
	}

}

int Population::partitionMembers(int start, int end) {
	int low = start;
	double pivot = m_members[end].getScore();

	for (int i = start; i < end; i++) {
		if (m_members[i].getScore() <= pivot) {
			Member temp = m_members[low];
			m_members[low] = m_members[i];
			m_members[i] = temp;
			low++;
		}
	}

	Member temp = m_members[low];
	m_members[low] = m_members[end];
	m_members[end] = temp;

	return low;
}

void Population::sortMembers(int start, int end) {
	//Using the quicksort algorithm
	if (start < end) {
		int pivot = partitionMembers(start, end);
		sortMembers(start, pivot - 1);
		sortMembers(pivot + 1, end);
	}
}

std::pair<Member, Member> Population::crossover(Member member1, Member member2) {
	//Creates 2 new children using randomly selected weights from each parent
	MyRandom rnd = MyRandom();

	Array<double> firstWeights = member1.getNetwork().getWeights();
	Array<double> secondWeights = member2.getNetwork().getWeights();

	for (int i = 0; i < firstWeights.size(); i++) {
		if (rnd.integer(2) == 1) {
			double temp = secondWeights[i];
			secondWeights[i] = firstWeights[i];
			firstWeights[i] = temp;
		}
	}

	Member child1 = Member(member1.getNetwork().getLayerSizes());
	Member child2 = Member(member2.getNetwork().getLayerSizes());
	child1.getNetwork().setWeights(firstWeights);
	child2.getNetwork().setWeights(secondWeights);

	return { child1, child2 };
}


void Population::evolve() {

	scoreMembers();
	sortMembers();

	// Generates children to fill all but the elite
	std::vector<Member> childGeneration = std::vector<Member>();

    TournamentSelection selectionAlgorithm(m_members, m_tournamentSize);

	// Create children
	for (unsigned int childIndex = 0; childIndex < m_members.size() - m_elitismSize; childIndex++) {
		Member& parent1 = selectionAlgorithm.select();
		Member& parent2 = selectionAlgorithm.select();
		std::pair<Member, Member> children = Population::crossover(parent1, parent2);
		childGeneration.push_back(children.first);
		childIndex++;
		if (childIndex < childGeneration.size()) {
			childGeneration.push_back(children.second);
		}
	}

	// Add children to population
	for (unsigned int popIndex = 0; popIndex < childGeneration.size(); popIndex++) {
		setMember(childGeneration[popIndex], popIndex);
	}

	// Mutate new members
	for (int i = 0; i < POP_SIZE; i++) {
		getMember(i).mutate(m_mutationRate);
	}
}

unsigned long Population::getGenerationCount() {
	return m_generationCount;
}

void Population::setGenerationCount(unsigned long generationCount) {
	m_generationCount = generationCount;
}

Array<int> Population::getLayerSizes() {
	return m_layerSizes;
}

Member Population::getChampion() {
	sortMembers();
	return m_members[m_members.size() - 1];
}
