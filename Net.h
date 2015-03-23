#pragma once

#include <vector>

class Neuron
{
private:
	double outputValue;
	std::vector<double> outputWeights;

public:
	void setOutputValue(double value)
	{
		outputValue = value;
	}

	static double transferFunction(double inputValue)
	{
		return std::tanh(inputValue);
	}

	void feedForward(double inputValue)
	{
		outputValue = Neuron::transferFunction(inputValue);
	}

	double getWeightedOutputValue(int outputNeuron) const
	{
		return outputValue * outputWeights[outputNeuron];
	}

	void createOutputWeights(unsigned int number)
	{
		outputWeights.clear();

		for (unsigned int i = 0; i < number; ++i)
		{
			outputWeights.push_back(std::rand() / (double)RAND_MAX);
		}
	}

	double getOutputValue() const
	{
		return outputValue;
	}
};

class Layer : public std::vector < Neuron >
{
public:
	Layer(unsigned int numNeurons)
	{
		for (unsigned int i = 0; i < numNeurons; ++i)
		{
			push_back(Neuron());
		}
	}

	void setOutputValues(const std::vector<double> & outputValues)
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

	void feedForward(const Layer &inputLayer)
	{
		int neuronNumber = 0;
		for (Neuron &neuron : *this)
		{
			neuron.feedForward(inputLayer.getWeightedSum(neuronNumber));
		}
	}

	double getWeightedSum(int outputNeuron) const
	{
		double sum = 0.0;

		for (const Neuron &neuron : *this)
		{
			sum += neuron.getWeightedOutputValue(outputNeuron);
		}

		return sum;
	}

	void connectTo(const Layer & nextLayer)
	{
		for (Neuron &neuron : *this)
		{
			neuron.createOutputWeights(nextLayer.size());
		}
	}
};

class Net : public std::vector < Layer >
{
public:
	Net(std::initializer_list<unsigned int> layerSizes)
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

			currentLayer.connectTo(nextLayer);
		}
	}

	void feedForward(const std::vector<double> &inputValues)
	{
		Layer &inputLayer = front();

		if (inputLayer.size() != inputValues.size())
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

	std::vector<double> getResult()
	{
		std::vector<double> result;

		const Layer &outputLayer = back();
		for (const Neuron &neuron : outputLayer)
		{
			result.push_back(neuron.getOutputValue());
		}

		return result;
	}
};