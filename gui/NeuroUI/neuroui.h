#ifndef NEUROUI_H
#define NEUROUI_H

#include <QMainWindow>

namespace Ui {
class NeuroUI;
}

class NeuroUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit NeuroUI(QWidget *parent = 0);
    ~NeuroUI();

private:
    Ui::NeuroUI *ui;
};

#endif // NEUROUI_H
