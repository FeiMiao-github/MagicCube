#include <QDebug>
#include "ug_axis.h"

Axis::Axis(QObject *parent)
    : QObject(parent)
{
    // qDebug() << "Alloc Axis " << this;
}

Axis::~Axis()
{
    // qDebug() << "Release Axis " << this;
}
