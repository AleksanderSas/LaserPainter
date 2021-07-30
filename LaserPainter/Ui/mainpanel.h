#ifndef MAINPANEL_H
#define MAINPANEL_H

#include <QWidget>
#include "Collection/shapecollection.h"
#include "shapedesigner.h"
#include "hardwareconnector.h"
#include "configuration.h"
#include <thread>
#include <QPushButton>
#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QScrollBar>
#include <QLabel>

class MainPanel : public QWidget
{
    Q_OBJECT
public:
    explicit MainPanel(QWidget *parent = nullptr);
    virtual ~MainPanel();

private:
    Configuration configuration;
    ShapeCollection shapeCollection;
    ShapeDesigner *shapeDesigner;
    HardwareConnector *connector = nullptr;
    void draw();
    std::thread *displayThread = nullptr;
    QPushButton *startButton;
    QSpinBox *pointsInput;
    QSpinBox *repeatsInput;
    QComboBox* shapeSelector;
    QCheckBox* drawLinesCheckbox;
    QCheckBox* enableWaitCircuid;
    QScrollBar *scaleBar;
    QLabel *scaleLabel;

signals:

public slots:
    void DisplayError();
    void OpenFile();
    void SaveFiel();
    void Clear();
    void hardwareDraw();
    void lineChecbox();
    void scaleUpdated(int value);
};

#endif // MAINPANEL_H
