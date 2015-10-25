#include "neuroui.h"
#include "ui_neuroui.h"

NeuroUI::NeuroUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NeuroUI)
{
    ui->setupUi(this);
}

NeuroUI::~NeuroUI()
{
    delete ui;
}

void NeuroUI::on_runButton_clicked()
{
    ui->logView->clear();

    if (m_netLearner == nullptr)
    {
        m_netLearner.reset(new NetLearner);
    }

    connect(m_netLearner.get(), &NetLearner::logMessage, this, &NeuroUI::logMessage);
    connect(m_netLearner.get(), &NetLearner::progress, this, &NeuroUI::progress);

    connect(m_netLearner.get(), &NetLearner::started, this, &NeuroUI::netLearnerStarted);
    connect(m_netLearner.get(), &NetLearner::finished, this, &NeuroUI::netLearnerFinished);

    m_netLearner->start();
}

void NeuroUI::logMessage(const QString &logMessage)
{
    ui->logView->addItem(logMessage);
    ui->logView->scrollToBottom();
}

void NeuroUI::netLearnerStarted()
{
    ui->runButton->setEnabled(false);
    ui->progressBar->setValue(0);
}

void NeuroUI::netLearnerFinished()
{
    ui->runButton->setEnabled(true);
    ui->progressBar->setValue(0);
}

void NeuroUI::progress(double progress)
{
    double range = ui->progressBar->maximum() - ui->progressBar->minimum();
    int value = ui->progressBar->minimum() + (int)(progress * range);

    ui->progressBar->setValue(value);
}
