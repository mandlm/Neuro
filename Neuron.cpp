#pragma once

#include "Neuron.h"

Neuron::Neuron(double value)
	: outputValue(value)
	, gradient(0)
{

}

void Neuron::setOutputValue(double value)
{
	outputValue = value;
}

double Neuron::transferFunction(double inputValue)
{
	return std::tanh(inputValue);
}

double Neuron::transferFunctionDerivative(double inputValue)
{
	return 1.0 - (inputValue * inputValue);
}

void Neuron::feedForward(double inputValue)
{
	outputValue = transferFunction(inputValue);
}

double Neuron::getWeightedOutputValue(unsigned int outputNeuron) const
{
	if (outputNeuron < outputWeights.size())
	{
		return outputValue * outputWeights[outputNeuron];
	}

	return 0.0;
}

void Neuron::createRandomOutputWeights(unsigned int numberOfWeights)
{
	outputWeights.clear();

	for (unsigned int i = 0; i < numberOfWeights; ++i)
	{
		outputWeights.push_back(std::rand() / (double)RAND_MAX);
	}
}

double Neuron::getOutputValue() const
{
	return outputValue;
}

void Neuron::calcOutputGradients(double targetValue)
{
	double delta = targetValue - outputValue;
	gradient = delta * transferFunctionDerivative(outputValue);
}

