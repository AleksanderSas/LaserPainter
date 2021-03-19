#ifndef MAINPANEL_H
#define MAINPANEL_H

#include <QWidget>
#include "shapecollection.h"
#include "bezierdesigner.h"
#include "hardwareconnector.h"
#include "configuration.h"
#include <thread>
#include <QPushButton>
#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>

class MainPanel : public QWidget
{
    Q_OBJECT
public:
    explicit MainPanel(QWidget *parent = nullptr);
    virtual ~MainPanel();

private:
    Configuration configuration;
    ShapeCollection shapeCollection;
    BezierDesigner *bezierDesigner;
    HardwareConnector *connector = nullptr;
    void draw();
    std::thread *displayThread = nullptr;
    QPushButton *startButton;
    QSpinBox *pointsInput;
    QSpinBox *repeatsInput;
    QComboBox* shapeSelector;
    QCheckBox* drawLinesCheckbox;

signals:

public slots:
    void OpenFile();
    void SaveFiel();
    void Clear();
    void hardwareDraw();
    void lineChecbox();
};

#endif // MAINPANEL_H
