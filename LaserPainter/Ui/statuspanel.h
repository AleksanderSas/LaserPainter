#ifndef STATUSPANEL_H
#define STATUSPANEL_H

#include <QWidget>
#include <QLabel>
#include "../Collection/shapecollection.h"

class StatusPanel : public QWidget
{
    Q_OBJECT

public:
    explicit StatusPanel(QWidget *parent = nullptr);
    void setValidation(int idx);
    void setPointInfo(Point* selectedPoint);

signals:

public slots:

private:
    QLabel *validationLabel;
    QLabel *pointLabel;
};

#endif // STATUSPANEL_H
