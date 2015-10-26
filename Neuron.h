#pragma once

#include <vector>
#include <list>

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
    double getWeightedOutputValue(size_t outputNeuron) const;
	
	void createRandomOutputWeights(size_t numberOfWeights);
	void createOutputWeights(std::list<double> weights);
	void createOutputWeights(size_t numberOfWeights, double weight);

	double getOutputValue() const;

	void calcOutputGradients(double targetValue);
	void calcHiddenGradients(const Layer &nextLayer);

	double getGradient() const;

	double getOutputWeight(size_t index) const;
	void setOutputWeight(size_t index, double value);
    size_t getNumOutputWeights() const;

private:
	static double transferFunction(double inputValue);
	static double transferFunctionDerivative(double inputValue);
	double sumDOW(const Layer &nextLayer) const;

};
