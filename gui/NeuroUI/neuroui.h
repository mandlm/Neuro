#ifndef NEUROUI_H
#define NEUROUI_H

#include <QMainWindow>

#include <memory>

#include "netlearner.h"

namespace Ui {
    class NeuroUI;
}

class NeuroUI : public QMainWindow
{
    Q_OBJECT

private:
    std::unique_ptr<NetLearner> m_netLearner;
    size_t m_logSize = 128;

public:
    explicit NeuroUI(QWidget *parent = 0);
    ~NeuroUI();

private slots:
    void on_runButton_clicked();
    void logMessage(const QString &logMessage);
    void netLearnerStarted();
    void netLearnerFinished();
    void progress(double progress);
    void setImage(const QImage &image);

private:
    Ui::NeuroUI *ui;
};

#endif // NEUROUI_H
