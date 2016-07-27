#ifndef ROTORLCD_H
#define ROTORLCD_H

#include "irotor.h"

#include <QWidget>
#include <QPixmap>
#include <QTimer>
#include <QHash>
#include <QDir>

class RotorLcd : public IRotor
{
    Q_OBJECT
public:
    RotorLcd(QWidget *parent = 0);
protected:
    void processSetValue(int degree);
    void paintEvent(QPaintEvent *);
private slots:
    void onTimer();

private:
    int m_degree;
    int m_degreePrev;
    QPixmap m_pixmap;
//    QPixmap m_pixmapArrow;
    QHash<int, QPixmap> m_pixmapArrowHash;
    QTimer *m_timer;
    static const QString cachePath;
    static const QString tmpFilePattern;
    QDir tmpFileDirectory;
};

#endif // ROTORLCD_H
