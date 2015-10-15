#include "Net.h"

Net::Net(std::initializer_list<unsigned int> layerSizes)
{
	if (layerSizes.size() < 3)
	{
		throw std::exception("A net needs at least 3 layers");
	}

	for (unsigned int numNeurons : layerSizes)
	{
		push_back(Layer(numNeurons));
	}

	for (auto layerIt = begin(); layerIt != end() - 1; ++layerIt)
	{
		Layer &currentLayer = *layerIt;
		const Layer &nextLayer = *(layerIt + 1);

		Neuron biasNeuron(1.0);
		currentLayer.push_back(biasNeuron);

		currentLayer.connectTo(nextLayer);
	}
}

void Net::feedForward(const std::vector<double> &inputValues)
{
	Layer &inputLayer = front();

	if (inputLayer.size() - 1 != inputValues.size())
	{
		throw std::exception("The number of input values has to match the input layer size");
	}

	inputLayer.setOutputValues(inputValues);

	for (auto layerIt = begin(); layerIt != end() - 1; ++layerIt)
	{
		const Layer &currentLayer = *layerIt;
		Layer &nextLayer = *(layerIt + 1);

		nextLayer.feedForward(currentLayer);
	}
}

std::vector<double> Net::getOutput()
{
	std::vector<double> result;

	const Layer &outputLayer = back();
	for (const Neuron &neuron : outputLayer)
	{
		result.push_back(neuron.getOutputValue());
	}

	return result;
}

void Net::backProp(const std::vector<double> &targetValues)
{
	const Layer &outputLayer = back();

	if (targetValues.size() != outputLayer.size())
	{
		throw std::exception("The number of target values has to match the output layer size");
	}

	std::vector<double> resultValues = getOutput();

	double rmsError = 0.0;
	for (unsigned int i = 0; i < resultValues.size(); ++i)
	{
		double delta = resultValues[i] - targetValues[i];
		rmsError += delta * delta;
	}
	rmsError = sqrt(rmsError / resultValues.size());
}
