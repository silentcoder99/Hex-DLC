#include "Network.h"
#include "MyRandom.h"
#include <ctime>
#include <iostream>

Neuron::Neuron(int numInputs): m_numWeights(numInputs + 1) {
	MyRandom rnd = MyRandom();

	//std::cout << "Created neuron with weights:\n";
	//Add weights
	for (int i = 0; i < m_numWeights; i++) {
		m_weights.push_back(rnd.real());
		//std::cout << m_weights[i] << "\n";
	}
	//std::cout << "\n";
}

Layer::Layer(int numNeurons, int inputsPerNeuron): m_numNeurons(numNeurons), m_inputsPerNeuron(inputsPerNeuron) {
	//Add neurons
	for (int i = 0; i < numNeurons; i++) {
		m_neurons.push_back(Neuron(inputsPerNeuron));
	}
}

Network::Network(int numInputs, std::vector<int> layerSizes, int numOutputs) {
	m_numInputs = numInputs;
	m_layerSizes = layerSizes;
	m_numOutputs = numOutputs;
	m_numHiddenLayers = layerSizes.size();
	//std::cout << "Created network:\n\n";

	//std::cout << "Created layer:\n\n";
	//Add first hidden layer (requires number of network inputs)
	m_layers.push_back(Layer(layerSizes[0], numInputs));

	//Add all other hidden layers
	for (int i = 1; i < m_numHiddenLayers; i++) {
		//std::cout << "Created layer:\n\n";
		m_layers.push_back(Layer(layerSizes[i], layerSizes[i - 1]));
	}

	//std::cout << "Created layer:\n\n";
	//Add output layer
	m_layers.push_back(Layer(numOutputs, layerSizes[m_numHiddenLayers - 1]));
}

std::vector<double> Network::getOutput(std::vector<double> inputs) {
	//std::cout << "Generating Network Output:\n\n";
	std::vector<double> outputs;

	for (auto layer : m_layers) {
		//std::cout << "Generating Layer Output:\n\n";

		outputs.clear();
		inputs.push_back(1); //Add bias input

		for (auto neuron : layer.m_neurons) {
			//std::cout << "Generating Neuron Output:\n\n";

			//Calculate activation
			double activation = 0;

			for (int i = 0; i < neuron.m_numWeights; i++) {
				//std::cout << "Generating Weighted Input:\n";
				//std::cout << "Input: " << inputs[i] << ", Weight: " << neuron.m_weights[i];
				//std::cout << ", Weighted Input: " << inputs[i] * neuron.m_weights[i] << "\n\n";
				activation += inputs[i] * neuron.m_weights[i];
			}
			//std::cout << "Neuron Output: " << sigmoid(activation) << "\n\n";
			outputs.push_back(sigmoid(activation));
		}
		//Output of this layer is the input of the next layer
		inputs = outputs;
	}

	return outputs;
}

int Network::getNumWeights() {
	int numWeights = 0;

	numWeights += (m_numInputs + 1) * m_layerSizes[0];

	for (int i = 1; i < m_numHiddenLayers; i++) {
		numWeights += (m_layerSizes[i - 1] + 1) * m_layerSizes[i];
	}

	numWeights += (m_layerSizes[m_numHiddenLayers - 1] + 1) * m_numOutputs;

	return numWeights;
}

std::vector<double> Network::getWeights() {
	std::vector<double> weights;

	for (auto layer : m_layers) {
		for (auto neuron : layer.m_neurons) {
			for (auto weight : neuron.m_weights) {
				weights.push_back(weight);
			}
		}
	}

	return weights;
}

void Network::setWeights(std::vector<double> weights) {
	int count = 0;

	//std::cout << "Setting Network Weights:\n\n";

	for (Layer& layer : m_layers) {

		//std::cout << "Setting Layer Weights:\n\n";

		for (Neuron& neuron : layer.m_neurons) {

			//std::cout << "Setting Neuron Weights:\n\n";

			neuron.m_weights.clear();

			//std::cout << "Clearing Neuron Weights" << neuron.m_weights.size() << "\n\n";

			for (int i = 0; i < neuron.m_numWeights; i++) {
				//std::cout << "Pushing weight: " << weights[count] << "\n";
				neuron.m_weights.push_back(weights[count]);
				count++;
			}
			//std::cout << neuron.m_weights.size() << "\n";
		}
	}
}