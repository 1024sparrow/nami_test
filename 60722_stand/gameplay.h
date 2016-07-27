#ifndef GAMEPLAY_H
#define GAMEPLAY_H

class IRotor;

class QLCDNumber;
class QPushButton;
class QSlider;
class QThread;

#include <QWidget>
#include <QList>

class Gameplay : public QWidget
{
    Q_OBJECT
public:
    Gameplay(bool startDemo, QWidget *parent = 0);
private slots:
    void onBnStartdemoClicked();
//    void onBnStopdemoClicked();
    void onSetValueNeeded(int value);
    void onDemoFinished();
    void setValueToNumberLCD(int);

private:
    QLCDNumber *lcdVlaue;
    QPushButton *bnRec;
    QPushButton *bnStopRec;
    QSlider *slider;
    QList<IRotor *> rotorList;
    QThread *threadDemo;
};

#endif // GAMEPLAY_H
