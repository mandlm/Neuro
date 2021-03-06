#include "mnistloader.h"

#include <fstream>

void MnistLoader::load(const std::string &databaseFileName, const std::string &labelsFileName)
{
    loadDatabase(databaseFileName);
    loadLabels(labelsFileName);
}

size_t MnistLoader::getSamleCount() const
{
    return samples.size();
}

const MnistLoader::MnistSample &MnistLoader::getSample(size_t index) const
{
    if (index >= samples.size())
    {
        throw std::runtime_error("MNIST sample index out of range");
    }

    return *(samples[index].get());
}

const MnistLoader::MnistSample &MnistLoader::getRandomSample() const
{
    size_t sampleIndex = (std::rand() * (samples.size() - 1)) / RAND_MAX;

    return *(samples[sampleIndex].get());
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
    if (magicNumber != DatabaseFileMagicNumber)
    {
        throw std::runtime_error("unexpected data reading MNIST database file");
    }

    int32_t sampleCount = readInt32(databaseFile);
    int32_t sampleWidth = readInt32(databaseFile);
    int32_t sampleHeight = readInt32(databaseFile);

    if (sampleWidth != SampleWidth || sampleHeight != SampleHeight)
    {
        throw std::runtime_error("unexpected sample size loading MNIST database");
    }

    samples.reserve(samples.size() + sampleCount);

    for (int32_t sampleIndex = 0; sampleIndex < sampleCount; ++sampleIndex)
    {
        std::unique_ptr<MnistSample> sample = std::make_unique<MnistSample>();

        databaseFile.read(reinterpret_cast<char *>(sample->data), sampleWidth * sampleHeight);

        samples.push_back(std::move(sample));
    }
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
    if (magicNumber != LabelFileMagicNumber)
    {
        throw std::runtime_error("unexpected data reading MNIST label file");
    }

    int32_t labelCount = readInt32(labelFile);
    if (labelCount != static_cast<int32_t>(samples.size()))
    {
        throw std::runtime_error("MNIST database and label files don't match in size");
    }

    auto sampleIt = samples.begin();
    for (int32_t labelIndex = 0; labelIndex < labelCount; ++labelIndex)
    {
        (*sampleIt++)->label = readInt8(labelFile);
    }
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

