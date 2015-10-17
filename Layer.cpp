#include "Layer.h"

Layer::Layer(size_t numNeurons)
{
	for (unsigned int i = 0; i < numNeurons; ++i)
	{
		push_back(Neuron());
	}
}

void Layer::setOutputValues(const std::vector<double> & outputValues)
{
	if (size() - 1 != outputValues.size())
	{
		throw std::exception("The number of output values has to match the layer size");
	}

	auto neuronIt = begin();
	for (const double &value : outputValues)
	{
		(neuronIt++)->setOutputValue(value);
	}
}

void Layer::feedForward(const Layer &inputLayer)
{
	int neuronNumber = 0;
	for (auto neuronIt = begin(); neuronIt != end(); ++neuronIt)
	{
		neuronIt->feedForward(inputLayer.getWeightedSum(neuronNumber++));
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
		neuron.createRandomOutputWeights(nextLayer.size());
	}
}

void Layer::updateInputWeights(Layer & prevLayer)
{
	static const double trainingRate = 0.8;

	for (size_t currentLayerIndex = 0; currentLayerIndex < size() - 1; ++currentLayerIndex)
	{
		Neuron &targetNeuron = at(currentLayerIndex);

		for (size_t prevLayerIndex = 0; prevLayerIndex < prevLayer.size(); ++prevLayerIndex)
		{
			Neuron &sourceNeuron = prevLayer.at(prevLayerIndex);

			sourceNeuron.setOutputWeight(currentLayerIndex, 
				sourceNeuron.getOutputWeight(currentLayerIndex) + 
				sourceNeuron.getOutputValue() * targetNeuron.getGradient() * trainingRate);
		}
	}
}
