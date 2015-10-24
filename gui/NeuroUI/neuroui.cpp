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
