#include "trainingdataloader.h"

#include <QImage>
#include <QColor>

TrainingDataLoader::TrainingDataLoader()
{

}

void TrainingDataLoader::addSamples(const QString &sourceFile, TrainingDataLoader::SampleId sampleId)
{
    QImage sourceImage;
    sourceImage.load(sourceFile);

    Sample sample;
    sample.first = sampleId;

    for (unsigned int y = 0; y < 8; ++y)
    {
        for (unsigned int x = 0; x < 8; ++x)
        {
            sample.second[x + y * 8] = qGray(sourceImage.pixel(x, y)) / 255.0;
        }
    }

    m_samples.push_back(sample);
}

