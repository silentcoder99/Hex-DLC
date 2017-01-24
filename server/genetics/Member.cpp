#include "Member.h"


Member::Member(Array<int> layerSizes): m_network(Network(NUM_INPUTS, layerSizes, NUM_OUTPUTS)) {
	m_score = 0;
}


double Member::getScore(){
    return m_score;
}

void Member::setScore(double score){
   m_score = score;
}

void Member::addScore(double points){
    m_score += points;
}

void Member::takeScore(double points){
    addScore(-points);
}

Network& Member::getNetwork(){
    return m_network;
}
