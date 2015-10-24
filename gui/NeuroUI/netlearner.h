#ifndef NETLEARNER_H
#define NETLEARNER_H

#include <QThread>

class NetLearner : public QThread
{
    Q_OBJECT

private:
    void run() Q_DECL_OVERRIDE;

signals:
    void logMessage(const QString &logMessage);
};

#endif // NETLEARNER_H
