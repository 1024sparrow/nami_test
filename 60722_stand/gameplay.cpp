#include "gameplay.h"
#include "demologics.h"
#include "irotor.h"
#include "rotorlcd.h"
#include "rotorlcdstupid.h"
//#include "rotorlcdqml.h"

#include <QBoxLayout>
#include <QScrollArea>
#include <QSlider>
#include <QPushButton>
#include <QLabel>
#include <QLCDNumber>
#include <QThread>

Gameplay::Gameplay(bool startDemo, QWidget *parent)
    :QWidget(parent)
{
    DemoLogics *demo = new DemoLogics();
    threadDemo = new QThread(this);
    {
        demo->moveToThread(threadDemo);

        connect(threadDemo, SIGNAL(started()), demo, SLOT(burnDemo()));
        connect(demo, SIGNAL(finished()), SLOT(onDemoFinished()));
        connect(demo, SIGNAL(setValueNeeded(int)), SLOT(onSetValueNeeded(int)));
    }

    bnRec = new QPushButton("start demo", this);
    {
        connect(bnRec, SIGNAL(clicked()), SLOT(onBnStartdemoClicked()));
    }
    bnStopRec = new QPushButton("stop demo", this);
    {
        //connect(bnStopRec, SIGNAL(clicked()), SLOT(onBnStopdemoClicked()));//leave this commented
        connect(bnStopRec, SIGNAL(clicked()), demo, SLOT(breakDemo()));
    }
    rotorList = QList<IRotor *>()
            << new RotorLcdStupid(this)
            << new RotorLcd(this)
//            << new RotorLcdQml(this)
            ;
    //~~~~~~~~~~~~~~~~~
    QScrollArea *sa = new QScrollArea(this);
    {
        QWidget *centralWidgetCandidate = new QWidget(sa);

        QBoxLayout *lay = new QHBoxLayout(centralWidgetCandidate);
        foreach (IRotor *i, rotorList)
        {
            QWidget *rotorContainer = new QWidget(centralWidgetCandidate);
            {
                QLabel *labelTitle = new QLabel(i->methodName(), rotorContainer);

                QBoxLayout *lay = new QVBoxLayout(rotorContainer);
                lay->setMargin(0);
                lay->addWidget(labelTitle);
                lay->addWidget(i);
            }
            lay->addWidget(rotorContainer);
        }
        sa->setWidget(centralWidgetCandidate);
    }

    lcdVlaue = new QLCDNumber(3, this);
    {
        QPalette pal = lcdVlaue->palette();
        pal.setColor(QPalette::Background, Qt::black);
        pal.setColor(QPalette::Foreground, Qt::green);
        lcdVlaue->setPalette(pal);
        lcdVlaue->setSegmentStyle(QLCDNumber::Flat);
        lcdVlaue->setAutoFillBackground(true);
    }

    QWidget *rightPanel = new QWidget(this);
    {
        QBoxLayout *lay = new QVBoxLayout(rightPanel);
        lay->setMargin(0);
        lay->addWidget(bnRec);
        lay->addWidget(bnStopRec);
        lay->addStretch();
        lay->addWidget(lcdVlaue);
    }

    slider = new QSlider(Qt::Vertical, this);
    {
        slider->setRange(0, 2000);
        slider->setValue(0);
        foreach (IRotor *i, rotorList)
        {
            connect(slider, SIGNAL(valueChanged(int)), i, SLOT(setValue(int)));
        }
        connect(slider, SIGNAL(valueChanged(int)), SLOT(setValueToNumberLCD(int)));
    }

    QBoxLayout *lay = new QHBoxLayout(this);
    lay->setMargin(0);
    lay->addWidget(sa);
    lay->addWidget(slider);
    lay->addWidget(rightPanel);

    bnRec->setEnabled(true);
    bnStopRec->setEnabled(false);

    if (startDemo)
        onBnStartdemoClicked();
}

void Gameplay::onBnStartdemoClicked()
{
    threadDemo->start();

    bnRec->setEnabled(false);
    bnStopRec->setEnabled(true);
}

//void Gameplay::onBnStopdemoClicked()
//{
//}

void Gameplay::onSetValueNeeded(int value)
{
    slider->setValue(value);
}

void Gameplay::onDemoFinished()
{
    bnRec->setEnabled(true);
    bnStopRec->setEnabled(false);
    threadDemo->exit();
}

void Gameplay::setValueToNumberLCD(int val)
{
    lcdVlaue->display(val / 10);
}
