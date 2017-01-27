#include "util/SuperArray.hpp"


class Neuron{
    int m_numWeights;
    Array<double> m_weights;
public:
    Neuron(int numInputs);
    Neuron() {};    

    double getWeight(int index);
    void setWeight(int index, double value);
    int getWeightCount();
};
