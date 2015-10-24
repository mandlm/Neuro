#include "netlearner.h"
#include "../../Net.h"

void NetLearner::run()
{
    try
    {
        Net myNet({2, 3, 1});

        size_t batchSize = 5000;
        size_t batchIndex = 0;
        double batchMaxError = 0.0;
        double batchMeanError = 0.0;

        size_t numIterations = 1000000;
        for (size_t iteration = 0; iteration < numIterations; ++iteration)
        {
            std::vector<double> inputValues =
            {
                std::rand() / (double)RAND_MAX,
                std::rand() / (double)RAND_MAX
            };

            std::vector<double> targetValues =
            {
                (inputValues[0] + inputValues[1]) / 2.0
            };

            myNet.feedForward(inputValues);

            std::vector<double> outputValues = myNet.getOutput();

            double error = outputValues[0] - targetValues[0];

            batchMeanError += error;
            batchMaxError = std::max<double>(batchMaxError, error);

            if (batchIndex++ == batchSize)
            {
                QString logString;

                logString.append("Batch error (");
                logString.append(QString::number(batchSize));
                logString.append(" iterations, max/mean): ");
                logString.append(QString::number(std::abs(batchMaxError)));
                logString.append(" / ");
                logString.append(QString::number(std::abs(batchMeanError / batchSize)));

                emit logMessage(logString);

                batchIndex = 0;
                batchMaxError = 0.0;
                batchMeanError = 0.0;
            }

            myNet.backProp(targetValues);
        }
    }
    catch (std::exception &ex)
    {
        QString logString("Error: ");
        logString.append(ex.what());
        emit logMessage(logString);
    }
}
