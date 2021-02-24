#ifndef MAINPANEL_H
#define MAINPANEL_H

#include <QWidget>
#include "bezier.h"
#include "shapecollection.h"
#include "bezierdesigner.h"
#include "hardwareconnector.h"
#include <thread>
#include <QPushButton>
#include <QSpinBox>
#include <QComboBox>

class MainPanel : public QWidget
{
    Q_OBJECT
public:
    explicit MainPanel(QWidget *parent = nullptr);

private:
    //Bezier bezier;
    ShapeCollection shapeCollection;
    BezierDesigner *bezierDesigner;
    HardwareConnector *connector = nullptr;
    void test();
    std::thread *displayThread = nullptr;
    QPushButton *startButton;
    QSpinBox *pointsInput;
    QSpinBox *repeatsInput;
    QComboBox* shapeSelector;

signals:

public slots:
    void OpenFile();
    void SaveFiel();
    void Clear();
    void hardwareDraw();
};

#endif // MAINPANEL_H
