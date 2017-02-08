#include "Neuron.h"
#include "MyRandom.h"


Neuron::Neuron(int numInputs) : m_weights(numInputs + 1) {
	MyRandom rnd = MyRandom();

	//std::cout << "Created neuron with weights:\n";
	//Add weights
	for (int i = 0; i < m_weights.size(); i++) {
		m_weights[i] = rnd.real(-1, 1);
		//std::cout << m_weights[i] << "\n";
	}
	//std::cout << "\n";
}

double Neuron::getWeight(int index){
    return m_weights[index];
}

void Neuron::setWeight(int index, double value){
    m_weights[index] = value;
}

int Neuron::getWeightCount(){
    return m_weights.size();
}
