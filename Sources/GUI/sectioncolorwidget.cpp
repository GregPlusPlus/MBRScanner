#include "sectioncolorwidget.h"

SectionColorWidget::SectionColorWidget(QWidget *parent) : QWidget(parent)
{
    m_percentage = 0;

    setMinimumSize(30, 30);
}

void SectionColorWidget::setColor(QColor color)
{
    m_color = color;

    update();
}

void SectionColorWidget::setPercentage(double percentage)
{
    m_percentage = percentage;

    update();
}

void SectionColorWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    QPainterPath path;
    path.addRoundedRect(QRectF(1.5, 1.5, width() - 2, height() - 2), 2, 2);

    QPen pen(QColor(50, 50, 50, 204), 1);
    p.setPen(pen);

    p.fillPath(path, m_color);
    p.drawPath(path);

    p.setPen(Qt::NoPen);
    p.setBrush(QColor(100, 100, 100, 100));

    int h = (int)((double)height() * (double)m_percentage);

    p.drawRect(1.5, height() - h, width() - 2, h);
}
