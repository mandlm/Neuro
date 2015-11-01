#ifndef MNISTLOADER_H
#define MNISTLOADER_H

#include <string>
#include <vector>
#include <memory>
#include <inttypes.h>

#include <QImage>

class MnistLoader
{
private:
    static const uint32_t DatabaseFileMagicNumber = 2051;
    static const uint32_t LabelFileMagicNumber = 2049;
    static const size_t SampleWidth = 28;
    static const size_t SampleHeight = 28;

public:
    template<size_t SAMPLE_WIDTH, size_t SAMPLE_HEIGHT>
    class Sample
    {
    public:
        uint8_t label;
        uint8_t data[SAMPLE_WIDTH * SAMPLE_HEIGHT];

        QImage toQImage() const
        {
            return QImage(data, SAMPLE_WIDTH, SAMPLE_HEIGHT, QImage::Format_Grayscale8);
        }
    };

    using MnistSample = Sample<SampleWidth, SampleHeight>;

private:
    std::vector<std::unique_ptr<MnistSample>> samples;

public:
    void load(const std::string &databaseFileName, const std::string &labelsFileName);

    size_t getSamleCount() const;
    const MnistSample &getSample(size_t index) const;
    const MnistSample &getRandomSample() const;

private:
    void loadDatabase(const std::string &fileName);
    void loadLabels(const std::string &fileName);

    static int8_t readInt8(std::ifstream &file);
    static int32_t readInt32(std::ifstream &file);
};

#endif // MNISTLOADER_H
