#include "util/SuperArray.hpp"
#include "Neuron.h"

class Layer {
	int m_inputsPerNeuron;
	Array<Neuron> m_neurons;
public:
	Layer(int numNeurons, int inputsPerNeuron);
	Layer() {};

    int getNeuronCount();
    int getInputsPerNeuron();
    Neuron& getNeuron(int index);
};

