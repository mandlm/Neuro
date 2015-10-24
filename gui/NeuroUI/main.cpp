#include "neuroui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NeuroUI w;
    w.show();

    return a.exec();
}
