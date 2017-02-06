#include "util/FastArray.h"


class Neuron{
    Array<double> m_weights;
public:
    Neuron(int numInputs);
    Neuron() {};    

    double getWeight(int index);
    void setWeight(int index, double value);
    int getWeightCount();
};
