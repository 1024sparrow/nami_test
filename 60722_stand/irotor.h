#ifndef IROTOR_H
#define IROTOR_H

#include <QWidget>

class IRotor : public QWidget
{
    Q_OBJECT
public:
    IRotor(const QString &methodName, QWidget *parent = 0);
    QString methodName() const;
public slots:
    void setValue(int);
protected:
    virtual void processSetValue(int) = 0;

private:
    QString methodNamePrivate;
};

#endif // IROTOR_H
