#include "rotorlcdstupid.h"

#include <QPainter>
#include <QTransform>
#include <QPixmap>
#include <QImage>
#include <QHash>

RotorLcdStupid::RotorLcdStupid(QWidget *parent)
    :IRotor(tr("the simplest"), parent), m_degree(0), m_degreePrev(0), m_d(0)
{
    m_pixmap = QPixmap(":ima/round.png");
    m_pixmapArrow = QPixmap(":ima/arrow.png");
    setFixedSize(m_pixmap.size());
    m_timer = new QTimer(this);
    {
        m_timer->setInterval(20);
        connect(m_timer, SIGNAL(timeout()), SLOT(onTimer()));
        m_timer->start();
    }

//    startTimer()
}

void RotorLcdStupid::processSetValue(int degree)
{
    m_degree = degree * 249 / 2000;
}

void RotorLcdStupid::paintEvent(QPaintEvent *)
{
    m_d = m_degreePrev - m_degree;

    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    painter.drawPixmap(0,0,m_pixmap);

    QTransform transform;
    {
        transform.translate(m_pixmap.width()/2, m_pixmap.height()/2);
        transform.rotate(qreal(m_degree) - qreal(1.8));
        transform.translate(-104, -32);
    }
    painter.setTransform(transform);

    painter.drawPixmap(0,0,m_pixmapArrow);
    m_degreePrev = m_degree;
}

void RotorLcdStupid::onTimer()
{
    if (isVisible())
        repaint();
}
