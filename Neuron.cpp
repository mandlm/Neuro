#pragma once

#include "Neuron.h"
#include "Layer.h"

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

void Neuron::createRandomOutputWeights(size_t numberOfWeights)
{
	outputWeights.clear();

	for (unsigned int i = 0; i < numberOfWeights; ++i)
	{
		outputWeights.push_back(std::rand() / (double)RAND_MAX);
	}
}

void Neuron::createOutputWeights(std::list<double> weights)
{
	outputWeights.clear();

	for (const double &weight : weights)
	{
		outputWeights.push_back(weight);
	}
}

void Neuron::createOutputWeights(size_t numberOfWeights, double weight)
{
	outputWeights.clear();

	for (unsigned int i = 0; i < numberOfWeights; ++i)
	{
		outputWeights.push_back(weight);
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

double Neuron::sumDOW(const Layer & nextLayer) const
{
	double sum = 0;

	for (size_t i = 0; i < outputWeights.size(); ++i)
	{
		sum += outputWeights[i] * nextLayer[i].getGradient();
	}

	return sum;
}

void Neuron::calcHiddenGradients(const Layer &nextLayer)
{
	double dow = sumDOW(nextLayer);
	gradient = dow * transferFunctionDerivative(outputValue);
}

double Neuron::getGradient() const
{
	return gradient;
}

double Neuron::getOutputWeight(size_t index) const
{
	return outputWeights.at(index);
}

void Neuron::setOutputWeight(size_t index, double value)
{
	outputWeights.at(index) = value;
}

