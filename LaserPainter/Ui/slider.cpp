#include "slider.h"
#include <QVBoxLayout>

Slider::Slider(QString prefix, QString sufix,int min, int max, unsigned int* value, QWidget *parent) :
    QWidget(parent),
    prefix(prefix), sufix(sufix), value(value)
{
    auto vbox = new QVBoxLayout(this);
    moveScaleLabel = new QLabel(this);
    bar = new QScrollBar(Qt::Orientation::Horizontal, this);
    bar->setRange(min, max);

    connect(bar, SIGNAL(valueChanged(int)), this, SLOT(myupdate(int)));

    vbox->addWidget(moveScaleLabel, 0, Qt::AlignTop);
    vbox->addWidget(bar, 0, Qt::AlignTop);
    vbox->setMargin(0);
    setValue(*value);
}

void Slider::myupdate(int value)
{
    moveScaleLabel->setText(prefix + QString::number(value) + sufix);
    *(this->value) = value;
}

void Slider::setValue(int value)
{
    myupdate(value);
    bar->setValue(value);
}
