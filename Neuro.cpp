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

		std::vector<double> inputValues =
		{
			0.1,
			0.7,
		};

		std::vector<double> targetValues = { 0.7 };

		myNet.feedForward(inputValues);

		std::vector<double> outputValues = myNet.getOutput();

		double error = outputValues[0] - targetValues[0];

		std::cout << "Error: ";
		std::cout << std::abs(error);
		std::cout << std::endl;

		myNet.backProp(targetValues);
	}
	catch (std::exception &ex)
	{
		std::cerr << "Error: " << ex.what() << std::endl;

		return 1;
	}

	return 0;
}