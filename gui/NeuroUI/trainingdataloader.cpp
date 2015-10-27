#include "trainingdataloader.h"

#include <sstream>

#include <QImage>
#include <QColor>

TrainingDataLoader::TrainingDataLoader()
{

}

void TrainingDataLoader::addSamples(const QString &sourceFile, TrainingDataLoader::SampleId sampleId)
{
    QImage sourceImage;
    if (sourceImage.load(sourceFile) == false)
    {
        std::ostringstream errorString;
        errorString << "error loading " << sourceFile.toStdString();

        throw std::runtime_error(errorString.str());
    }

    QSize scanWindow(32, 32);
    QPoint scanPosition(0, 0);

    while (scanPosition.y() + scanWindow.height() < sourceImage.height())
    {
        scanPosition.setX(0);

        while (scanPosition.x() + scanWindow.width() < sourceImage.width())
        {
            Sample sample;
            sample.first = sampleId;

            for (int y = 0; y < scanWindow.height(); ++y)
            {
                for (int x = 0; x < scanWindow.width(); ++x)
                {
                    QRgb color = sourceImage.pixel(scanPosition.x() + x, scanPosition.y() + y);
                    sample.second[x + y * scanWindow.height()] = qGray(color) / 255.0;
                }
            }

            m_samples.push_back(sample);

            scanPosition.rx() += scanWindow.width();
        }

        scanPosition.ry() += scanWindow.height();
    }
}

const TrainingDataLoader::Sample &TrainingDataLoader::getRandomSample() const
{
    size_t sampleIndex = (std::rand() * m_samples.size()) / RAND_MAX;

    auto it = m_samples.cbegin();
    for (size_t index = 0; index < sampleIndex; ++index)
    {
        it++;
    }
    return *it;
}

