#pragma once 
#include <vector>
#include <math.h>
#include "SuperArray.hpp"

struct Neuron {
	int m_numWeights;
	Array<double> m_weights;
	Neuron(int);
	Neuron() {};
};

struct Layer {
	int m_inputsPerNeuron;
	int m_numNeurons;
	Array<Neuron> m_neurons;
	Layer(int, int);
	Layer() {};
};

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

inline double sigmoid(double x) {
	return 1 / (1 + exp(-x));
}
