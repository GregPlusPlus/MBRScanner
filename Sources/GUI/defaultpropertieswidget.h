#ifndef DEFAULTPROPERTIESWIDGET_H
#define DEFAULTPROPERTIESWIDGET_H

#include <QWidget>
#include <QLabel>

#include <QVBoxLayout>

#include <QFont>

class DefaultPropertiesWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DefaultPropertiesWidget(QWidget *parent = nullptr);

signals:

public slots:

private:
    QVBoxLayout *m_mainLayout;
    QLabel *mw_title;
    QLabel *mw_message;
};

#endif // DEFAULTPROPERTIESWIDGET_H
