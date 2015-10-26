#include "errorplotter.h"

#include <QPainter>

ErrorPlotter::ErrorPlotter(QWidget *parent)
    : QWidget(parent)
    , m_maxErrorValue(0.0)
{
}

QSize ErrorPlotter::minimumSizeHint() const
{
    return QSize(100, 100);
}

QSize ErrorPlotter::sizeHint() const
{
    return QSize(400, 200);
}

void ErrorPlotter::clear()
{
    m_errorValues.clear();
    m_maxErrorValue = 0.0;

    update();
}

void ErrorPlotter::addErrorValue(double errorValue)
{
    m_errorValues.push_back(errorValue);
    m_maxErrorValue = std::max<double>(m_maxErrorValue, errorValue);

    update();
}

void ErrorPlotter::paintEvent(QPaintEvent *)
{
    if (m_errorValues.empty() || m_maxErrorValue == 0)
    {
        return;
    }

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.translate(0.0, height());
    painter.scale(1.0, -1.0);

    double errorValueScale = height() / m_maxErrorValue;

    auto errorValueIt = m_errorValues.crbegin();

    double prevErrorValue = *errorValueIt;
    errorValueIt++;

    int xPos = width() - 2;
    while(errorValueIt != m_errorValues.crend() && xPos >= 0)
    {
        double currentErrorValue = *errorValueIt;

        painter.drawLine(xPos + 1, prevErrorValue * errorValueScale,
                         xPos, currentErrorValue * errorValueScale);

        prevErrorValue = currentErrorValue;
        errorValueIt++;
        xPos--;
    }
}
