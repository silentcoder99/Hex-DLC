#include "Member.h"
#include "MyRandom.h"


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

void Member::mutate(int mutationRate){
    MyRandom rnd = MyRandom();

	Array<double> weights = getNetwork().getWeights();

	for (unsigned int i = 0; i < weights.size(); i++) {
		if (rnd.real(0, 1) < ( mutationRate / 100.0 )) {
			weights[i] = rnd.real(-1, 1);
		}
	}

	getNetwork().setWeights(weights);
}
