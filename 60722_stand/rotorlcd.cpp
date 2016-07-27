#include "rotorlcd.h"

#include <QPainter>
#include <QTransform>
#include <QPixmap>
#include <QImage>
#include <QDir>
#include <QDebug>

struct MyColor
{
    int red;
    int green;
    int blue;
    int alpha;
    MyColor()
    {
        red = 0;
        green = 0;
        blue = 0;
        alpha = 0;
    }
};

const QString RotorLcd::cachePath = "cache";
const QString RotorLcd::tmpFilePattern = "%1.png";

RotorLcd::RotorLcd(QWidget *parent)
    :IRotor(tr("smoothed"), parent), m_degree(0), m_degreePrev(0)
{
    m_pixmap = QPixmap(":ima/round.png");
    QPixmap m_pixmapArrow = QPixmap(":ima/arrow.png");
    setFixedSize(m_pixmap.size());
    m_timer = new QTimer(this);
    {
        m_timer->setInterval(20);
        connect(m_timer, SIGNAL(timeout()), SLOT(onTimer()));
        m_timer->start();
    }
    bool cacheBuildNeeded = false;
    {
        QDir dir(QDir::current());
        if (!dir.cd(cachePath))
        {
            cacheBuildNeeded = true;
            dir.mkdir(cachePath);
            if (!dir.cd(cachePath))
                qDebug() << "can't create a direcory "<<cachePath;
        }
        tmpFileDirectory = dir;
        if (!cacheBuildNeeded)
        {
            for (int i = 0 ; i < 360 ; ++i)
            {
                if (!dir.exists(tmpFilePattern.arg(i)))
                {
                    cacheBuildNeeded = true;
                    break;
                }
            }
        }
    }

    if (cacheBuildNeeded)
    {
        qDebug()<<"build cache";
        QPainter tmpPainter;
        QPixmap tmpPixmap = QPixmap(m_pixmap.size());
        QHash<QPair<int, int>, MyColor> integral;
        {
            tmpPixmap.fill(Qt::transparent);
            for (int i = 0 ; i < 360 ; ++i)
            {
                QImage tmpImg = tmpPixmap.toImage();
                tmpPainter.begin(&tmpImg);
                tmpPainter.setRenderHints(QPainter::SmoothPixmapTransform);
                QTransform transform;
                {
                    transform.translate(m_pixmap.width()/2, m_pixmap.height()/2);
                    transform.rotate(i);
                    transform.translate(-104, -32);
                }
                tmpPainter.setTransform(transform);
                tmpPainter.drawPixmap(0,0,m_pixmapArrow);
                tmpPainter.end();

                QImage imageToSave;
                {
                    QPixmap s(m_pixmap.size());
                    s.fill(Qt::transparent);
                    imageToSave = s.toImage();
                }
                for (int x = 0, xC = tmpPixmap.width() ; x < xC ; ++x)
                {
                    for (int y = 0, yC = tmpPixmap.height() ; y < yC ; ++y)
                    {
                        QRgb col = tmpImg.pixel(x, y);
                        MyColor &retVal = integral[qMakePair(x, y)];
                        int r(qRed(col)), g(qGreen(col)), b(qBlue(col)), a(qAlpha(col));
                        retVal.alpha += a;
                        retVal.red += r;
                        retVal.green += g;
                        retVal.blue += b;

                        imageToSave.setPixel(x, y,
                                             qRgba(
                                                 retVal.red / (i + 1),
                                                 retVal.green / (i + 1),
                                                 retVal.blue / (i + 1),
                                                 retVal.alpha / (i + 1)));
                    }
                }
                imageToSave.save(tmpFileDirectory.absoluteFilePath(tmpFilePattern.arg(i)));
                m_pixmapArrowHash.insert(i, QPixmap::fromImage(imageToSave));
            }
        }
    }
    else
    {
        qDebug()<<"load cache";
        for (int i = 0 ; i < 360 ; ++i)
        {
            m_pixmapArrowHash.insert(i, QPixmap(tmpFileDirectory.absoluteFilePath(tmpFilePattern.arg(i))));
        }
    }
}

void RotorLcd::processSetValue(int degree)
{
    m_degree = degree * 249 / 2000;
}

void RotorLcd::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    painter.drawPixmap(0,0,m_pixmap);
    QPixmap m_pixmapArrow = m_pixmapArrowHash.value(qAbs(m_degreePrev - m_degree));
    if (!m_pixmapArrow.isNull())
    {
        QTransform transform;
        {
            transform.translate(m_pixmap.width()/2, m_pixmap.height()/2);
            transform.rotate(qreal(qMin(m_degree, m_degreePrev)) - qreal(1.8));
            transform.translate(-m_pixmap.width()/2, -m_pixmap.height()/2);
        }
        painter.setTransform(transform);
        painter.drawPixmap(0,0,m_pixmapArrow);
    }
    m_degreePrev = m_degree;
}

void RotorLcd::onTimer()
{
    if (isVisible())
        repaint();
}
