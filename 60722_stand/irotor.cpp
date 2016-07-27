#include "irotor.h"

IRotor::IRotor(const QString &methodName, QWidget *parent)
    :QWidget(parent), methodNamePrivate(methodName)
{
}

void IRotor::setValue(int val)
{
    processSetValue(val);
}

QString IRotor::methodName() const
{
    return methodNamePrivate;
}
