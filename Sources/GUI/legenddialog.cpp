#include "legenddialog.h"

LegendDialog::LegendDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle(tr("Legend"));
    setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint);

    m_mainLayout = new QGridLayout;

    setLayout(m_mainLayout);
}

LegendDialog::~LegendDialog()
{

}

void LegendDialog::setPlugin(PropertiesPlugin *plugin)
{
    m_plugin = plugin;

    if(m_plugin)
    {
        updateSections();
    }
}

void LegendDialog::updateSections()
{
    int size = (int)(sqrt(m_plugin->getSections().length())) + 1;

    for(int i = 0 ; i < m_sectionWidgets.length() ; i++)
    {
        delete m_sectionWidgets[i];
    }

    m_sectionWidgets.clear();

    for(int i = 0 ; i < m_plugin->getSections().length() ; i++)
    {
        SectionWidget *w = new SectionWidget(m_plugin->getSections().at(i), this);

        m_sectionWidgets.append(w);
    }

    for(int i = 0 ; i < size ; i++)
    {
        for(int j = 0 ; j < size ; j++)
        {
            int item = i * size + j;

            if(item < m_plugin->getSections().length())
            {
                m_mainLayout->addWidget(m_sectionWidgets.at(item), i, j, 1, 1);
            }
            else
            {
               return;
            }
        }
    }
}
