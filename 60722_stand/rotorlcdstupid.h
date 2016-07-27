#ifndef ROTORLCDSTUPID_H
#define ROTORLCDSTUPID_H

#include "irotor.h"

#include <QWidget>
#include <QPixmap>
#include <QTimer>

class RotorLcdStupid : public IRotor
{
    Q_OBJECT
public:
    RotorLcdStupid(QWidget *parent = 0);
protected:
    void processSetValue(int);
    void paintEvent(QPaintEvent *);
private slots:
    void onTimer();

private:
    int m_degree;
    int m_degreePrev;
    QPixmap m_pixmap;
    QPixmap m_pixmapArrow;
    QTimer *m_timer;
    qreal m_d;
};

#endif // ROTORLCDSTUPID_H
