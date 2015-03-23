#pragma once

#include <vector>

#include "Layer.h"

class Net : public std::vector < Layer >
{
public:
	Net(std::initializer_list<unsigned int> layerSizes);

	void feedForward(const std::vector<double> &inputValues);
	std::vector<double> getResult();
	void backProp(const std::vector<double> &targetValues);
};