#include "Net.h"

#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cmath>

Net::Net()
{

}

Net::Net(std::initializer_list<size_t> layerSizes)
{
    initialize(layerSizes);
}

Net::Net(const std::string &filename)
{
    load(filename);
}

void Net::initialize(std::initializer_list<size_t> layerSizes)
{
    clear();

    if (layerSizes.size() < 2)
    {
        throw std::runtime_error("A net needs at least 2 layers");
    }

    for (size_t numNeurons : layerSizes)
    {
        push_back(Layer(numNeurons));
    }

    for (auto layerIt = begin(); layerIt != end() - 1; ++layerIt)
    {
        Layer &currentLayer = *layerIt;
        const Layer &nextLayer = *(layerIt + 1);

        currentLayer.addBiasNeuron();

        currentLayer.connectTo(nextLayer);
    }
}

void Net::feedForward(const std::vector<double> &inputValues)
{
	Layer &inputLayer = front();

	if (inputLayer.size() - 1 != inputValues.size())
	{
        throw std::runtime_error("The number of input values has to match the input layer size");
	}

	inputLayer.setOutputValues(inputValues);

	for (auto layerIt = begin(); layerIt != end() - 1; ++layerIt)
	{
		const Layer &currentLayer = *layerIt;
		Layer &nextLayer = *(layerIt + 1);

		nextLayer.feedForward(currentLayer);
    }
}

void Net::feedForward(const double *inputValues)
{
    Layer &inputLayer = front();

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
	Layer &outputLayer = back();

	if (targetValues.size() != outputLayer.size())
	{
        throw std::runtime_error("The number of target values has to match the output layer size");
	}

	std::vector<double> resultValues = getOutput();
	size_t numResultValues = resultValues.size();

	// calculate rms error
	double rmsError = 0.0;

	for (unsigned int i = 0; i < numResultValues; ++i)
	{
		rmsError += std::pow(resultValues[i] - targetValues[i], 2);
	}

	rmsError = std::sqrt(rmsError / numResultValues);

	// calculate output neuron gradients 
	for (unsigned int i = 0; i < numResultValues; ++i)
	{
		outputLayer[i].calcOutputGradients(targetValues[i]);
	}

	// calculate hidden neuron gradients
	for (auto it = end() - 1; (it - 1) != begin(); --it)
	{
		Layer &hiddenLayer = *(it - 1);
		Layer &nextLayer = *it;

		for (Neuron &neuron : hiddenLayer)
		{
			neuron.calcHiddenGradients(nextLayer);
		}
	}

	// update the input weights
	for (auto it = end() - 1; it != begin(); --it)
	{
		Layer &currentLayer = *it;
		Layer &prevLayer = *(it - 1);

		currentLayer.updateInputWeights(prevLayer);
    }
}

void Net::save(const std::string &filename)
{
    std::ofstream outFile;
    outFile.open(filename);
    if (!outFile.is_open())
    {
        throw std::runtime_error("unable to open output file");
    }

    outFile << size() << std::endl;
    for (const Layer &layer : *this)
    {
		outFile << layer.size() << std::endl;
        outFile << layer.hasBiasNeuron() << std::endl;

        for (const Neuron &neuron : layer)
        {
            size_t numOutputWeights = neuron.getNumOutputWeights();
            outFile << numOutputWeights << std::endl;

            for (size_t outputWeightIndex = 0; outputWeightIndex < numOutputWeights; ++outputWeightIndex)
            {
                outFile << neuron.getOutputWeight(outputWeightIndex) << std::endl;
            }
        }
    }

    outFile.close();
}

void Net::load(const std::string &filename)
{
    std::ifstream inFile;
    inFile.open(filename, std::ios::binary);
    if (!inFile.is_open())
    {
        throw std::runtime_error("unable to open input file");
    }

    clear();

	std::string buffer;

	getline(inFile, buffer);
    size_t numLayers = std::stol(buffer);

    for (size_t layerIndex = 0; layerIndex < numLayers; ++layerIndex)
    {

		getline(inFile, buffer);
		size_t numNeurons = std::stol(buffer);

		getline(inFile, buffer);
		bool hasBiasNeuron = std::stol(buffer) != 0;

        size_t numNeuronsWithoutBiasNeuron = hasBiasNeuron ? numNeurons - 1 : numNeurons;

        Layer newLayer(numNeuronsWithoutBiasNeuron);
        if (hasBiasNeuron)
        {
            newLayer.addBiasNeuron();
        }

        for (size_t neuronIndex = 0; neuronIndex < numNeurons; ++neuronIndex)
        {
			getline(inFile, buffer);
			size_t numWeights = std::stol(buffer);

			std::list<double> outputWeights;
            for (size_t weightIndex = 0; weightIndex < numWeights; ++weightIndex)
            {
				getline(inFile, buffer);
				outputWeights.push_back(std::stod(buffer));
            }

			newLayer.at(neuronIndex).createOutputWeights(outputWeights);
		}

        push_back(newLayer);
    }

	inFile.close();
}
