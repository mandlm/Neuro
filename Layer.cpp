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
    for (size_t neuronNumber = 0; neuronNumber < sizeWithoutBiasNeuron(); ++neuronNumber)
	{
		at(neuronNumber).feedForward(inputLayer.getWeightedSum(neuronNumber));
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
		neuron.createOutputWeights(nextLayer.sizeWithoutBiasNeuron(), 1.0);
	}
}

void Layer::updateInputWeights(Layer & prevLayer)
{
	static const double trainingRate = 0.3;

	for (size_t targetLayerIndex = 0; targetLayerIndex < sizeWithoutBiasNeuron(); ++targetLayerIndex)
	{
		const Neuron &targetNeuron = at(targetLayerIndex);

		for (size_t sourceLayerIndex = 0; sourceLayerIndex < prevLayer.size(); ++sourceLayerIndex)
		{
			Neuron &sourceNeuron = prevLayer.at(sourceLayerIndex);
		
			sourceNeuron.setOutputWeight(targetLayerIndex, 
				sourceNeuron.getOutputWeight(targetLayerIndex) + 
				sourceNeuron.getOutputValue() * targetNeuron.getGradient() * trainingRate);
		}
	}
}

void Layer::addBiasNeuron()
{
	push_back(Neuron(1.0));
	hasBiasNeuron = true;
}

size_t Layer::sizeWithoutBiasNeuron() const
{
	if (hasBiasNeuron)
	{
		return size() - 1;
	}
	else
	{
		return size();
	}
}
