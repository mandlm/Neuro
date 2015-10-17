#pragma once

#include <vector>

class Layer;

class Neuron
{
private:
	double outputValue;
	std::vector<double> outputWeights;
	double gradient;

public:
	Neuron(double value = 1.0);

	void setOutputValue(double value);
	void feedForward(double inputValue);
	double getWeightedOutputValue(unsigned int outputNeuron) const;
	void createRandomOutputWeights(size_t numberOfWeights);
	double getOutputValue() const;

	void calcOutputGradients(double targetValue);
	void calcHiddenGradients(const Layer &nextLayer);

	double getGradient() const;

	double getOutputWeight(size_t index) const;
	void setOutputWeight(size_t index, double value);

private:
	static double transferFunction(double inputValue);
	static double transferFunctionDerivative(double inputValue);
	double sumDOW(const Layer &nextLayer) const;

};
