#pragma once 
#include <vector>
#include <math.h>

struct Neuron {
	int m_numWeights;
	std::vector<double> m_weights;
	Neuron(int);
};

struct Layer {
	int m_inputsPerNeuron;
	int m_numNeurons;
	std::vector<Neuron> m_neurons;
	Layer(int, int);
};

class Network {
	int m_numInputs;
	int m_numHiddenLayers;
	std::vector<int> m_layerSizes;
	std::vector<Layer> m_layers;
	int m_numOutputs;
public:
	Network(int, std::vector<int>, int);
	std::vector<double> getOutput(std::vector<double>);
	int getNumWeights();
	std::vector<double> getWeights();
	void setWeights(std::vector<double>);
};

inline double sigmoid(double x) {
	return 1 / (1 + exp(-x));
}
