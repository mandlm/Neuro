#include <iostream>
#include <exception>

#include "Net.h"

int main()
{
	try
	{
		std::cout << "Neuro running" << std::endl;

		Net myNet({ 3, 4, 2 });

		myNet.feedForward({ 1.0, 2.0, 3.0 });

		std::vector<double> result = myNet.getResult();

		std::cout << "Result: ";
		for (double &value : result)
		{
			std::cout << value << " ";
		}
		std::cout << std::endl;
	}
	catch (std::exception &ex)
	{
		std::cerr << "Error: " << ex.what() << std::endl;

		return 1;
	}

	return 0;
}