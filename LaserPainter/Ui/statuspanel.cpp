#include "statuspanel.h"
#include <QVBoxLayout>

StatusPanel::StatusPanel(QWidget *parent) : QWidget(parent)
{
    auto layout = new QHBoxLayout(this);
    validationLabel = new QLabel(this);
    pointLabel = new QLabel("No point selected", this);
    layout->addWidget(validationLabel, 1, Qt::AlignTop);
    layout->addWidget(pointLabel, 1, Qt::AlignTop);
}

void StatusPanel::setValidation(int invalidPointIdx)
{
    if(invalidPointIdx >= 0)
    {
        validationLabel->setText(QString("Invalid point: ") + QString::number(invalidPointIdx));
    }
    else
    {
        validationLabel->setText(QString("Collection is valid"));
    }
}

void StatusPanel::setPointInfo(Point* selectedPoint, int idx)
{
    pointLabel->setText(QString("Point Type: ") + getShapeName(selectedPoint->type).c_str() + " - " + QString::number((idx)));
}
