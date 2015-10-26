#ifndef ERRORPLOTTER_H
#define ERRORPLOTTER_H

#include <QWidget>

class ErrorPlotter : public QWidget
{
    Q_OBJECT

private:
    std::list<double> m_errorValues;
    double m_maxErrorValue;

public:
    explicit ErrorPlotter(QWidget *parent = 0);

    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

    void clear();

protected:
    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;

signals:

public slots:
    void addErrorValue(double errorValue);
};

#endif // ERRORPLOTTER_H
