#pragma once

#include <vector>

#include "Layer.h"

class Net : public std::vector < Layer >
{
public:
	Net(std::initializer_list<size_t> layerSizes);
    Net(const std::string &filename);

	void feedForward(const std::vector<double> &inputValues);
	std::vector<double> getOutput();
	void backProp(const std::vector<double> &targetValues);

    void save(const std::string &filename);
    void load(const std::string &filename);
};
