#include <iostream>
#include <exception>
#include <algorithm>

#include <assert.h>

#include "Net.h"

const double pi = std::acos(-1);

int main()
{
	try
	{
		std::cout << "Neuro running" << std::endl;

		Net myNet({ 2, 3, 1 });

		size_t batchSize = 5000;
		size_t batchIndex = 0;
		double batchMaxError = 0.0;
		double batchMeanError = 0.0;

		size_t numIterations = 1000000;
		for (size_t iteration = 0; iteration < numIterations; ++iteration)
		{
			std::vector<double> inputValues =
			{
				std::rand() / (double)RAND_MAX,
				std::rand() / (double)RAND_MAX
			};

			std::vector<double> targetValues =
			{
				(inputValues[0] + inputValues[1]) / 2.0
			};

			myNet.feedForward(inputValues);

			std::vector<double> outputValues = myNet.getOutput();

			double error = outputValues[0] - targetValues[0];

			batchMeanError += error;
			batchMaxError = std::max<double>(batchMaxError, error);

			if (batchIndex++ == batchSize)
			{
				std::cout << "Batch error (" << batchSize << " iterations, max/mean): ";
				std::cout << std::abs(batchMaxError);
				std::cout << " / ";
				std::cout << std::abs(batchMeanError / batchSize);
				std::cout << std::endl;

				batchIndex = 0;
				batchMaxError = 0.0;
				batchMeanError = 0.0;
			}

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