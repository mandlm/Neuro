#ifndef TRAININGDATALOADER_H
#define TRAININGDATALOADER_H

#include <utility>
#include <list>
#include <string>

#include <QString>

class TrainingDataLoader
{
public:
    using SampleData = double[64];
    using SampleId = unsigned int;
    using Sample = std::pair<SampleId, SampleData>;

private:
    std::list<Sample> m_samples;

public:
    TrainingDataLoader();

    void addSamples(const QString &sourceFile, SampleId sampleId);
};

#endif // TRAININGDATALOADER_H
