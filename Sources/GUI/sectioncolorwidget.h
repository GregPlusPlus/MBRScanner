#ifndef SECTIONCOLORWIDGET_H
#define SECTIONCOLORWIDGET_H

#include <QWidget>

#include <QPaintEvent>
#include <QPainter>
#include <QColor>

class SectionColorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SectionColorWidget(QWidget *parent = nullptr);
    void setColor(QColor color);
    void setPercentage(double percentage);

signals:

public slots: 

private:
    QColor m_color;
    double m_percentage;

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // SECTIONCOLORWIDGET_H
