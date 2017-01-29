#pragma once 
#include <vector>
#include <math.h>
#include "util/FastArray.h"
#include "Layer.h"


class Network {
	int m_numInputs;
	int m_numHiddenLayers;
	Array<int> m_layerSizes;
	Array<Layer> m_layers;
	int m_numOutputs;
public:
	Network(int, Array<int>, int);
	Array<double> getOutput(Array<double>);
	int getNumWeights();
	Array<double> getWeights();
	void setWeights(Array<double>);
	Array<int> getLayerSizes();
};


