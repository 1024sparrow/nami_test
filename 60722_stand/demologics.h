#ifndef DEMOLOGICS_H
#define DEMOLOGICS_H

#include <atomic>

#include <QObject>

class DemoLogics : public QObject
{
    Q_OBJECT
public:
    DemoLogics(QObject *parent = 0);
signals:
    void setValueNeeded(int speed);
    void finished();

    void rd();
    void rb();
    void sd();
    void sb();
    void sdn();
    void rbn();
public slots:
    void burnDemo();
    void breakDemo();
private slots:
    void makeRapidDispersal();
    void makeRapidBrake();
    void makeSlowDispersal();
    void makeSlowBrake();
    void makeSlowDispersalWithNoise();
    void makeRapidBrakeWithNoise();

private:
    std::atomic<bool> ifBreakRequested;
};

#endif // DEMOLOGICS_H
