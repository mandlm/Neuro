#ifndef TRAININGDATALOADER_H
#define TRAININGDATALOADER_H

#include <utility>
#include <list>
#include <string>

#include <QString>

class TrainingDataLoader
{
public:
    using SampleData = double[32*32];
    using SampleId = unsigned int;
    using Sample = std::pair<SampleId, SampleData>;

private:
    std::list<Sample> m_samples;

public:
    TrainingDataLoader();

    void addSamples(const QString &sourceFile, SampleId sampleId);

    const Sample &getRandomSample() const;
};

#endif // TRAININGDATALOADER_H
