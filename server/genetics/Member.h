#pragma once
#include "Network.h"
#include "SuperArray.hpp"

struct Member {
	Network m_network;
	double m_score;
	Member(Array<int> layerSizes);
};
