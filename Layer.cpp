#include "Layer.h"

Layer::Layer(unsigned int numNeurons)
{
	for (unsigned int i = 0; i < numNeurons; ++i)
	{
		push_back(Neuron());
	}
}

void Layer::setOutputValues(const std::vector<double> & outputValues)
{
	if (size() != outputValues.size())
	{
		throw std::exception("The number of output values has to match the layer size");
	}

	auto valueIt = outputValues.begin();
	for (Neuron &neuron : *this)
	{
		neuron.setOutputValue(*valueIt++);
	}
}

void Layer::feedForward(const Layer &inputLayer)
{
	int neuronNumber = 0;
	for (Neuron &neuron : *this)
	{
		neuron.feedForward(inputLayer.getWeightedSum(neuronNumber));
	}
}

double Layer::getWeightedSum(int outputNeuron) const
{
	double sum = 0.0;

	for (const Neuron &neuron : *this)
	{
		sum += neuron.getWeightedOutputValue(outputNeuron);
	}

	return sum;
}

void Layer::connectTo(const Layer & nextLayer)
{
	for (Neuron &neuron : *this)
	{
		neuron.createOutputWeights(nextLayer.size());
	}
}
