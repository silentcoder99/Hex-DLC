#pragma once
#include "Network.h"
#include "SuperArray.hpp"

#define NUM_INPUTS 121
#define NUM_OUTPUTS 2

class Member {
	Network m_network;
	double m_score;
public:
	Member(Array<int> layerSizes);

    // Score funcions
    double getScore();
    void setScore(double score);
    void addScore(double points);
    void takeScore(double points);

    // Network
    Network& getNetwork();
};
