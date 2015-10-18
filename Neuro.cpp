#include <iostream>
#include <exception>

#include "Net.h"

int main()
{
	try
	{
		std::cout << "Neuro running" << std::endl;

		std::vector<double> inputValues = { 0.1, 0.2, 0.8 };
		std::vector<double> targetValues = { 0.8 };

		Net myNet({ inputValues.size(), 4, targetValues.size() });

		for (int i = 0; i < 200; ++i)
		{
			myNet.feedForward(inputValues);

			std::vector<double> outputValues = myNet.getOutput();

			std::cout << "Result: ";
			for (double &value : outputValues)
			{
				std::cout << value << " ";
			}
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