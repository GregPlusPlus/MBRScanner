#include "tools.h"

QString Tools::getPasswordAsMask(QString password, QString mask)
{
    QString str;

    for(int i(0) ; i < password.length() ; i++)
    {
        str += mask;
    }

    return str;
}

QFrame *Tools::createSeparator(QFrame::Shape shape)
{
    QFrame* line = new QFrame();
    line->setFrameShape(shape);
    line->setFrameShadow(QFrame::Raised);
    return line;
}

void Tools::applyStyleSheet(QString path)
{
    QFile File(path);
    File.open(QFile::ReadOnly);

    QString StyleSheet = QLatin1String(File.readAll());

    File.close();

    qApp->setStyleSheet(StyleSheet);
}
