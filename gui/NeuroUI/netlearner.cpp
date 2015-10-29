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
        emit progress(0.0);

        MnistLoader mnistLoader;
        mnistLoader.load("../NeuroUI/MNIST Aatabase/train-images.idx3-ubyte",
                         "../NeuroUI/MNIST Aatabase/train-labels.idx1-ubyte");

        emit logMessage("done");
        emit progress(0.0);

        Net digitClassifier({32*32, 16*16, 32, 1});

        timer.start();

        size_t numIterations = 10000;
        for (size_t iteration = 0; iteration < numIterations; ++iteration)
        {
            std::vector<double> targetValues =
            {
                //trainingSample.first / 10.0
            };

            //digitClassifier.feedForward(trainingSample.second);

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
