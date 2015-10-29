#ifndef MNISTLOADER_H
#define MNISTLOADER_H

#include <string>

class MnistLoader
{
public:
    MnistLoader();

    void load(const std::string &databaseFileName, const std::string &labelsFileName);
};

#endif // MNISTLOADER_H
