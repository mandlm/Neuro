#pragma once

#include <vector>

#include "Neuron.h"

class Layer : public std::vector < Neuron >
{
public:
	Layer(size_t numNeurons);

	void setOutputValues(const std::vector<double> & outputValues);
	void feedForward(const Layer &inputLayer);
	double getWeightedSum(int outputNeuron) const;
	void connectTo(const Layer & nextLayer);

	void updateInputWeights(Layer &prevLayer);
};
