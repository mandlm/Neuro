#include "netlearner.h"
#include "../../Net.h"
#include "trainingdataloader.h"

#include <QElapsedTimer>

void NetLearner::run()
{
    try
    {
        QElapsedTimer timer;

        emit logMessage("Loading training data...");
        emit progress(0.0);

        TrainingDataLoader dataLoader;
        dataLoader.addSamples("../NeuroUI/training data/mnist_train0.jpg", 0);
        emit progress(0.1);
        dataLoader.addSamples("../NeuroUI/training data/mnist_train1.jpg", 1);
        emit progress(0.2);
        dataLoader.addSamples("../NeuroUI/training data/mnist_train2.jpg", 2);
        emit progress(0.3);
        dataLoader.addSamples("../NeuroUI/training data/mnist_train3.jpg", 3);
        emit progress(0.4);
        dataLoader.addSamples("../NeuroUI/training data/mnist_train4.jpg", 4);
        emit progress(0.5);
        dataLoader.addSamples("../NeuroUI/training data/mnist_train5.jpg", 5);
        emit progress(0.6);
        dataLoader.addSamples("../NeuroUI/training data/mnist_train6.jpg", 6);
        emit progress(0.7);
        dataLoader.addSamples("../NeuroUI/training data/mnist_train7.jpg", 7);
        emit progress(0.8);
        dataLoader.addSamples("../NeuroUI/training data/mnist_train8.jpg", 8);
        emit progress(0.9);
        dataLoader.addSamples("../NeuroUI/training data/mnist_train9.jpg", 9);
        emit progress(1.0);

        emit logMessage("done");
        emit progress(0.0);

        Net digitClassifier({32*32, 16*16, 32, 1});

        timer.start();

        size_t numIterations = 10000;
        for (size_t iteration = 0; iteration < numIterations; ++iteration)
        {
            const TrainingDataLoader::Sample &trainingSample = dataLoader.getRandomSample();

            std::vector<double> targetValues =
            {
                trainingSample.first / 10.0
            };

            digitClassifier.feedForward(trainingSample.second);

            std::vector<double> outputValues = digitClassifier.getOutput();

            double error = outputValues[0] - targetValues[0];

            QString logString;

            logString.append("Error: ");
            logString.append(QString::number(std::abs(error)));

            emit logMessage(logString);
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
}
