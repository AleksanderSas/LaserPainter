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
    QCheckBox* enableLaser;
    QCheckBox* enableMove;
    QSpinBox *pointsInput;
    QSpinBox *moveSpeedInput;
    QSpinBox *repeatsInput;
    QComboBox* shapeSelector;
    QCheckBox* drawLinesCheckbox;
    QCheckBox* drawShapeCheckbox;
    QCheckBox* enableWaitCircuid;
    QScrollBar *scaleBar;
    QScrollBar *moveScaleBar;
    QLabel *scaleLabel;
    QLabel *moveScaleLabel;
    UnReDoPanel *unrePanel;

    QSpinBox* CreateAndAddSpinner(const char* title, int initValue, QVBoxLayout* layout);
    void updateConfiguration();
    void setTitle(QString fileName);
    void loadProject(std::string fileName);

signals:

public slots:
    void displayError();
    void openFile();
    void saveFile();
    void clear();
    void hardwareDraw();
    void lineChecbox();
    void shapeChecbox();
    void scaleUpdated(int value);
    void moveScaleUpdated(int value);
    void enableLaserSlot(int state);
};

#endif // MAINPANEL_H
