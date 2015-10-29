#include "mnistloader.h"

#include <fstream>
#include <functional>
#include <memory>
#include <list>

#include <intrin.h>

MnistLoader::MnistLoader()
{

}

void MnistLoader::load(const std::string &databaseFileName, const std::string &labelsFileName)
{
    loadDatabase(databaseFileName);
    loadLabels(labelsFileName);
}

void MnistLoader::loadDatabase(const std::string &fileName)
{
    std::ifstream databaseFile;
    databaseFile.open(fileName, std::ios::binary);

    if (!databaseFile.is_open())
    {
        throw std::runtime_error("unable to open MNIST database file");
    }

    int32_t magicNumber = readInt32(databaseFile);
    if (magicNumber != 2051)
    {
        throw std::runtime_error("unexpected data reading MNIST database file");
    }

    int32_t sampleCount = readInt32(databaseFile);
    int32_t sampleWidth = readInt32(databaseFile);
    int32_t sampleHeight = readInt32(databaseFile);

    std::list<std::unique_ptr<int8_t[]>> samples;

    for (size_t sampleIndex = 0; sampleIndex < sampleCount; ++sampleIndex)
    {
        std::unique_ptr<int8_t[]> sampleData = std::make_unique<int8_t[]>(sampleWidth * sampleHeight);

        databaseFile.read(reinterpret_cast<char *>(sampleData.get()), sampleWidth * sampleHeight);

        samples.push_back(std::move(sampleData));
    }

    return;
}

void MnistLoader::loadLabels(const std::string &fileName)
{
    std::ifstream labelFile;
    labelFile.open(fileName, std::ios::binary);

    if (!labelFile.is_open())
    {
        throw std::runtime_error("unable to open MNIST label file");
    }

    int32_t magicNumber = readInt32(labelFile);
    if (magicNumber != 2049)
    {
        throw std::runtime_error("unexpected data reading MNIST label file");
    }

    int32_t labelCount = readInt32(labelFile);

    std::list<int8_t> labels;

    for (size_t labelIndex = 0; labelIndex < labelCount; ++labelIndex)
    {
        labels.push_back(readInt8(labelFile));
    }

    return;
}

int8_t MnistLoader::readInt8(std::ifstream &file)
{
    int8_t buf8;
    file.read(reinterpret_cast<char *>(&buf8), sizeof(buf8));
    return buf8;
}

int32_t MnistLoader::readInt32(std::ifstream &file)
{
    int32_t buf32;
    file.read(reinterpret_cast<char *>(&buf32), sizeof(buf32));
    return _byteswap_ulong(buf32);
}

