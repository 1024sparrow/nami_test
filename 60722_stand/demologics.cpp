#include "demologics.h"

#include <chrono>
#include <thread>

#include <QThread>
#include <QApplication>

inline void mySleep(qreal n)
{
//    for (long j = 0 ; j < n * 0x1111 ; j+=2)
//    {
//        if (j%3)
//            qApp->processEvents();
//        else
//            j--;
//    }

    std::this_thread::sleep_for(std::chrono::microseconds(static_cast<int>(n * 1000)));
}

DemoLogics::DemoLogics(QObject *parent)
    :QObject(parent), ifBreakRequested(false)
{
    connect(this, SIGNAL(rd()), SLOT(makeRapidDispersal()));
    connect(this, SIGNAL(rb()), SLOT(makeRapidBrake()));
    connect(this, SIGNAL(sd()), SLOT(makeSlowDispersal()));
    connect(this, SIGNAL(sb()), SLOT(makeSlowBrake()));
    connect(this, SIGNAL(sdn()), SLOT(makeSlowDispersalWithNoise()));
    connect(this, SIGNAL(rbn()), SLOT(makeRapidBrakeWithNoise()));
}

void DemoLogics::burnDemo()
{
    ifBreakRequested = false;

//    makeRapidDispersal();
//    makeSlowBrake();

//    makeSlowDispersal();
//    makeRapidBrake();

//    makeSlowDispersalWithNoise();
//    makeRapidBrakeWithNoise();

    emit rd();
}

void DemoLogics::breakDemo()
{
    ifBreakRequested = true;
}

void DemoLogics::makeRapidDispersal()
{
    if (ifBreakRequested)
    {
        emit finished();
        return;
    }
    else
    {
        for (int i = 0 ; i < 2000 ; ++i)
        {
            qApp->processEvents();
            if (ifBreakRequested)
            {
                emit finished();
                return;
            }
            emit setValueNeeded(i);
            mySleep(2);
        }
    }
    emit sb();
}

void DemoLogics::makeRapidBrake()
{
    if (ifBreakRequested)
    {
        emit finished();
        return;
    }
    else
    {
        for (int i = 2000 ; i >= 0 ; --i)
        {
            qApp->processEvents();
            if (ifBreakRequested)
            {
                emit finished();
                return;
            }
            emit setValueNeeded(i);
            mySleep(2);
        }
    }
    emit sdn();
}

void DemoLogics::makeSlowDispersal()
{
    if (ifBreakRequested)
    {
        emit finished();
        return;
    }
    else
    {

        for (int i = 0 ; i < 2000 ; ++i)
        {
            qApp->processEvents();
            if (ifBreakRequested)
            {
                emit finished();
                return;
            }
            emit setValueNeeded(i);
            mySleep(10);
        }
    }
    emit rb();
}

void DemoLogics::makeSlowBrake()
{
    if (ifBreakRequested)
    {
        emit finished();
        return;
    }
    else
    {
        for (int i = 2000 ; i >= 0 ; --i)
        {
            qApp->processEvents();
            if (ifBreakRequested)
            {
                emit finished();
                return;
            }
            emit setValueNeeded(i);
            mySleep(10);
        }
    }
    emit sd();
}

void DemoLogics::makeSlowDispersalWithNoise()
{
    if (ifBreakRequested)
    {
        emit finished();
        return;
    }
    else
    {
        for (int i = 0 ; i < 2000 ; ++i)
        {
            qApp->processEvents();
            if (ifBreakRequested)
            {
                emit finished();
                return;
            }
            for (int j = 0 ; j < 16 ; ++j)
            {
                emit setValueNeeded(i + qrand()%100 - 50);
                mySleep(1);
            }
        }
    }
    emit rbn();
}

void DemoLogics::makeRapidBrakeWithNoise()
{
    if (ifBreakRequested)
    {
        emit finished();
        return;
    }
    else
    {
        for (int i = 2000 ; i >= 0 ; --i)
        {
            qApp->processEvents();
            if (ifBreakRequested)
            {
                emit finished();
                return;
            }
            for (int j = 0 ; j < 16 ; ++j)
            {
                emit setValueNeeded(i + qrand()%30 - 15);
                mySleep(0.5);
            }
        }
    }
    emit finished();
}
