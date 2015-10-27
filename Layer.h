#pragma once

#include <vector>

#include "Neuron.h"

class Layer : public std::vector < Neuron >
{
private:
    bool m_hasBiasNeuron = false;

public:
	Layer(size_t numNeurons);

	void setOutputValues(const std::vector<double> & outputValues);
    void setOutputValues(const double *outputValues);

	void feedForward(const Layer &inputLayer);
    double getWeightedSum(size_t outputNeuron) const;
	void connectTo(const Layer & nextLayer);

	void updateInputWeights(Layer &prevLayer);

	void addBiasNeuron();

    bool hasBiasNeuron() const;
	size_t sizeWithoutBiasNeuron() const;
};
