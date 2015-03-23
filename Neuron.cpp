#pragma once

#include "Neuron.h"

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
	outputValue = Neuron::transferFunction(inputValue);
}

double Neuron::getWeightedOutputValue(int outputNeuron) const
{
	return outputValue * outputWeights[outputNeuron];
}

void Neuron::createOutputWeights(unsigned int number)
{
	outputWeights.clear();

	for (unsigned int i = 0; i < number; ++i)
	{
		outputWeights.push_back(std::rand() / (double)RAND_MAX);
	}
}

double Neuron::getOutputValue() const
{
	return outputValue;
}
