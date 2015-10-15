#pragma once

#include <vector>

class Neuron
{
private:
	double outputValue;
	std::vector<double> outputWeights;
	double gradient;

public:
	Neuron(double value = 1.0);

	void setOutputValue(double value);
	static double transferFunction(double inputValue);
	static double transferFunctionDerivative(double inputValue);
	void feedForward(double inputValue);
	double getWeightedOutputValue(unsigned int outputNeuron) const;
	void createRandomOutputWeights(unsigned int numberOfWeights);
	double getOutputValue() const;

	void calcOutputGradients(double targetValue);
	//void calcHiddenGradients(const Layer &prevLayer);
};
