#include "Network.h"
#include "MyRandom.h"
#include <ctime>
#include <iostream>

Neuron::Neuron(int numInputs) : m_numWeights(numInputs + 1), m_weights(numInputs + 1) {
	MyRandom rnd = MyRandom();

	//std::cout << "Created neuron with weights:\n";
	//Add weights
	for (int i = 0; i < m_numWeights; i++) {
		m_weights[i] = rnd.real(-1, 1);
		//std::cout << m_weights[i] << "\n";
	}
	//std::cout << "\n";
}

Layer::Layer(int numNeurons, int inputsPerNeuron): 
	m_numNeurons(numNeurons),
	m_inputsPerNeuron(inputsPerNeuron),
	m_neurons(numNeurons){
	//Add neurons
	for (int i = 0; i < numNeurons; i++) {
		m_neurons[i] = Neuron(inputsPerNeuron);
	}
}

Network::Network(int numInputs, Array<int> layerSizes, int numOutputs) :
	m_layerSizes(layerSizes),
	m_layers(layerSizes.size() + 1) {

	m_numInputs = numInputs;
	m_numOutputs = numOutputs;
	m_numHiddenLayers = layerSizes.size();
	//std::cout << "Created network:\n\n";

	//std::cout << "Created layer:\n\n";
	//Add first hidden layer (requires number of network inputs)
	m_layers[0] = Layer(layerSizes[0], numInputs);

	//Add all other hidden layers
	for (int i = 1; i < m_numHiddenLayers; i++) {
		//std::cout << "Created layer:\n\n";
		m_layers[i] = Layer(layerSizes[i], layerSizes[i - 1]);
	}

	//std::cout << "Created layer:\n\n";
	//Add output layer
	m_layers[m_numHiddenLayers] = Layer(numOutputs, layerSizes[m_numHiddenLayers - 1]);
}

Array<double> Network::getOutput(Array<double> inputs) {
	//std::cout << "Generating Network Output:\n\n";
	Array<double> output;

	for (int layerIndex = 0; layerIndex < m_layers.size(); layerIndex++) {
		//std::cout << "Generating Layer Output:\n\n";

		Layer& currentLayer = m_layers[layerIndex];

		output = Array<double>(currentLayer.m_neurons.size());

		for (int neuronIndex = 0; neuronIndex < currentLayer.m_neurons.size(); neuronIndex++) {
			//std::cout << "Generating Neuron Output:\n\n";
			Neuron& currentNeuron = currentLayer.m_neurons[neuronIndex];
			//Calculate activation
			double activation = 0;

			for (int i = 0; i < currentNeuron.m_numWeights - 1; i++) {
				//std::cout << "Generating Weighted Input:\n";
				//std::cout << "Input: " << inputs[i] << ", Weight: " << neuron.m_weights[i];
				//std::cout << ", Weighted Input: " << inputs[i] * neuron.m_weights[i] << "\n\n";
				activation += inputs[i] * currentNeuron.m_weights[i];
			}

			// Biased input
			activation += currentNeuron.m_weights[currentNeuron.m_numWeights - 1];

			//std::cout << "Neuron Output: " << sigmoid(activation) << "\n\n";
			output[neuronIndex] = sigmoid(activation);
		}
		//Output of this layer is the input of the next layer
		inputs = output;
	}

	return output;
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

Array<double> Network::getWeights() {

	int weightCount = 0;
	for (int layerIndex = 0; layerIndex < m_layers.size(); layerIndex++) {
		Layer& layer = m_layers[layerIndex];

		for (int neuronIndex = 0; neuronIndex < layer.m_neurons.size(); neuronIndex++) {
			Neuron& neuron = layer.m_neurons[neuronIndex];

			for (int weightIndex = 0; weightIndex < neuron.m_weights.size(); weightIndex++) {
				double weight = neuron.m_weights[weightIndex];

				weightCount++;
			}
		}
	}

	Array<double> weights = Array<double>(weightCount);
	int outputWeightIndex = 0;
	for (int layerIndex = 0; layerIndex < m_layers.size(); layerIndex++) {
		Layer& layer = m_layers[layerIndex];

		for (int neuronIndex = 0; neuronIndex < layer.m_neurons.size(); neuronIndex++) {
			Neuron& neuron = layer.m_neurons[neuronIndex];

			for (int weightIndex = 0; weightIndex < neuron.m_weights.size(); weightIndex++) {
				double weight = neuron.m_weights[weightIndex];

				weights[outputWeightIndex] = weight;
				outputWeightIndex++;
			}
		}
	}

	return weights;
}

void Network::setWeights(Array<double> weights) {
	int count = 0;

	//std::cout << "Setting Network Weights:\n\n";

	for (int layerIndex = 0; layerIndex < m_layers.size(); layerIndex++) {
		Layer& layer = m_layers[layerIndex];

		for (int neuronIndex = 0; neuronIndex < layer.m_neurons.size(); neuronIndex++) {
			Neuron& neuron = layer.m_neurons[neuronIndex];

			//std::cout << "Setting Neuron Weights:\n\n";

			neuron.m_weights = Array<double>(neuron.m_numWeights);

			//std::cout << "Clearing Neuron Weights" << neuron.m_weights.size() << "\n\n";

			for (int i = 0; i < neuron.m_numWeights; i++) {
				//std::cout << "Pushing weight: " << weights[count] << "\n";
				neuron.m_weights[i] = weights[count];
				count++;
			}
			//std::cout << neuron.m_weights.size() << "\n";
		}
	}
}

Array<int> Network::getLayerSizes() {
	return m_layerSizes;
}