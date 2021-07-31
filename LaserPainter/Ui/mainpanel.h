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
#include <QVBoxLayout>

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
    QSpinBox *moveSpeedInput;
    QSpinBox *repeatsInput;
    QComboBox* shapeSelector;
    QCheckBox* drawLinesCheckbox;
    QCheckBox* enableWaitCircuid;
    QScrollBar *scaleBar;
    QLabel *scaleLabel;

    QSpinBox* CreateAndAddSpinner(char* title, int initValue, QVBoxLayout* layout);
    void updateConfiguration();

signals:

public slots:
    void displayError();
    void openFile();
    void saveFile();
    void clear();
    void hardwareDraw();
    void lineChecbox();
    void scaleUpdated(int value);
};

#endif // MAINPANEL_H
