#ifndef MAINPANEL_H
#define MAINPANEL_H

#include <QWidget>
#include "Collection/project.h"
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
    Project project;
    ShapeDesigner *shapeDesigner;
    ShapeDesigner *moveDesigner;
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
    void SaveFile();
    void Clear();
    void hardwareDraw();
    void lineChecbox();
    void scaleUpdated(int value);
};

#endif // MAINPANEL_H
