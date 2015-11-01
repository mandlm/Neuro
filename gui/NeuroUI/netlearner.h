#ifndef NETLEARNER_H
#define NETLEARNER_H

#include <QThread>

class NetLearner : public QThread
{
    Q_OBJECT

private:
    bool cancel = false;

private:
    void run() Q_DECL_OVERRIDE;

signals:
    void logMessage(const QString &logMessage);
    void progress(double progress);
    void currentNetError(double error);
    void sampleImageLoaded(const QImage &image);

public slots:
    void cancelLearning();
};

#endif // NETLEARNER_H
