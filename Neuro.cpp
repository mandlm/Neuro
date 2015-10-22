#include <iostream>
#include <exception>
#include <algorithm>

#include "Net.h"

int main()
{
	try
	{
		std::cout << "Neuro running" << std::endl;

		Net myNet({ 2, 3, 1 });

		size_t numIterations = 10000;
		for (size_t iteration = 0; iteration < numIterations; ++iteration)
		{
			std::vector<double> inputValues =
			{
				std::rand() / (double)RAND_MAX,
				std::rand() / (double)RAND_MAX
			};

			std::vector<double> targetValues =
			{
				*std::max_element(inputValues.begin(), inputValues.end())
			};

			myNet.feedForward(inputValues);

			std::vector<double> outputValues = myNet.getOutput();

			double error = outputValues[0] - targetValues[0];

			std::cout << "Error: ";
			std::cout << std::abs(error);
			std::cout << std::endl;

			myNet.backProp(targetValues);
		}
	}
	catch (std::exception &ex)
	{
		std::cerr << "Error: " << ex.what() << std::endl;

		return 1;
	}

	return 0;
}