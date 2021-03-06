#include "netlearner.h"
#include "../../Net.h"
#include "mnistloader.h"

#include <QElapsedTimer>
#include <QImage>

void NetLearner::run()
{
    try
    {
        QElapsedTimer timer;

        emit logMessage("Loading training data...");

        MnistLoader mnistLoader;
        mnistLoader.load("../NeuroUI/MNIST Database/train-images.idx3-ubyte",
                         "../NeuroUI/MNIST Database/train-labels.idx1-ubyte");

        emit logMessage("done");

        Net digitClassifier({28*28, 256, 1});

        timer.start();

        size_t numIterations = 100000;
        for (size_t iteration = 0; iteration < numIterations && cancel == false; ++iteration)
        {
            auto trainingSample = mnistLoader.getRandomSample();

//            emit logMessage(QString("training sample ") + QString::number(trainingSample.label));
            emit sampleImageLoaded(trainingSample.toQImage());

            std::vector<double> targetValues =
            {
                trainingSample.label / 10.0
            };

            std::vector<double> trainingData;
            trainingData.reserve(28*28);
            for (const uint8_t &val : trainingSample.data)
            {
                trainingData.push_back(val / 255.0);
            }

            digitClassifier.feedForward(trainingData);

            std::vector<double> outputValues = digitClassifier.getOutput();

            double error = outputValues[0] - targetValues[0];

            emit logMessage(QString("Error: ") + QString::number(std::abs(error)));
            emit currentNetError(error);
            emit progress((double)iteration / (double)numIterations);

            digitClassifier.backProp(targetValues);
        }

        QString timerLogString;
        timerLogString.append("Elapsed time: ");
        timerLogString.append(QString::number(timer.elapsed() / 1000.0));
        timerLogString.append(" seconds");

        emit logMessage(timerLogString);

        digitClassifier.save("DigitClassifier.nnet");
    }
    catch (std::exception &ex)
    {
        QString logString("Error: ");
        logString.append(ex.what());
        emit logMessage(logString);
    }

    cancel = false;
}

void NetLearner::cancelLearning()
{
    cancel = true;
}
