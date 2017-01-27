#include "Layer.h"


Layer::Layer(int numNeurons, int inputsPerNeuron): 
	m_inputsPerNeuron(inputsPerNeuron),
	m_neurons(numNeurons){

	//Add neurons
	for (int i = 0; i < numNeurons; i++) {
		m_neurons[i] = Neuron(inputsPerNeuron);
	}
}


int Layer::getNeuronCount(){
    return m_neurons.size();
}

int Layer::getInputsPerNeuron(){
    return m_inputsPerNeuron;
}

Neuron& Layer::getNeuron(int index){
    return m_neurons[index];
}
