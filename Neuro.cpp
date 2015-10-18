#include <iostream>
#include <exception>

#include "Net.h"

int main()
{
	try
	{
		std::cout << "Neuro running" << std::endl;

		Net myNet({ 3, 2, 1 });

		for (int i = 0; i < 100000; ++i)
		{
			std::vector<double> inputValues =
			{
				std::rand() / (double)RAND_MAX,
				std::rand() / (double)RAND_MAX,
				std::rand() / (double)RAND_MAX
			};

			std::vector<double> targetValues = { inputValues[2] };

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