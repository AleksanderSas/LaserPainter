#include "mainpanel.h"
#include "bezierdesigner.h"
#include "hardwareconnector.h"
#include <QLabel>
#include <QFrame>
#include <QStatusBar>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFileDialog>
#include <thread>
#include <QMessageBox>

#include "math.h"
void drawHeard(Bezier &b);

MainPanel::MainPanel(QWidget *parent) : QWidget(parent)
{
    auto *hbox = new QHBoxLayout(this);
    auto *vbox = new QVBoxLayout();
    auto* shapeSelector = new QComboBox(this);
    bezierDesigner = new BezierDesigner(shapeCollection, shapeSelector, this);
    startButton = new QPushButton("Start", this);
    auto* clearButton = new QPushButton("Clear", this);
    auto* saveButton = new QPushButton("Save", this);
    auto* openButton = new QPushButton("Open", this);
    shapeSelector->addItems(QStringList{BEZIER_, LINE_, CIRCLE_});

    auto* pointsLabel = new QLabel("Points" ,this);
    pointsInput = new QSpinBox(this);
    pointsInput->setRange(10, 5000);
    pointsInput->setValue(300);
    auto* repeatsLabel = new QLabel("Repeats" ,this);
    repeatsInput = new QSpinBox(this);
    repeatsInput->setRange(10, 5000);
    repeatsInput->setValue(100);

    vbox->setSpacing(5);
    vbox->addWidget(startButton, 0, Qt::AlignTop);
    vbox->addWidget(clearButton, 0, Qt::AlignTop);
    vbox->addWidget(saveButton, 0, Qt::AlignTop);
    vbox->addWidget(openButton, 0, Qt::AlignTop);
    vbox->addStretch(5);
    vbox->addWidget(shapeSelector, 0, Qt::AlignTop);
    vbox->addStretch(5);
    vbox->addWidget(pointsLabel, 0, Qt::AlignTop);
    vbox->addWidget(pointsInput, 0, Qt::AlignTop);
    vbox->addStretch(2);
    vbox->addWidget(repeatsLabel, 0, Qt::AlignTop);
    vbox->addWidget(repeatsInput, 0, Qt::AlignTop);
    vbox->addStretch(90);

    hbox->addItem(vbox);
    hbox->addWidget(bezierDesigner, 5);

    connect(openButton, SIGNAL(clicked()), this, SLOT(OpenFile()));
    connect(saveButton, SIGNAL(clicked()), this, SLOT(SaveFiel()));
    connect(clearButton, SIGNAL(clicked()), this, SLOT(Clear()));
    connect(startButton, SIGNAL(clicked()), this, SLOT(hardwareDraw()));

    connector = new HardwareConnector();
}

/*#define PI 3.1415
void kolo(Bezier& b, int x, int y, int r)
{
    const int n = 11;
    for(int i  = 0; i < n; i++)
    {
        b.Add(x + sin(PI * 2 * i / n) * r, y + cos(PI * 2 * i / n) * r);
    }
    b.Add(x, y + r);
}*/

void MainPanel::hardwareDraw()
{
    if(connector->run)
    {
        connector->run = false;
        displayThread ->join();
        delete displayThread;
        displayThread = nullptr;
        startButton -> setText("Start");
        return;
    }
    if(displayThread != nullptr)
    {
        displayThread ->join();
        delete displayThread;
    }
    displayThread = new std::thread(&MainPanel::test, this);
    startButton -> setText("Stop");
}

void MainPanel::test()
{
    connector->drawBezier(shapeCollection, pointsInput->value(), repeatsInput->value());
    startButton -> setText("Start");
}

void MainPanel::SaveFiel()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save"), "/home");
    shapeCollection.save(fileName.toStdString().c_str());
}

void MainPanel::Clear()
{
    shapeCollection.clear();
    bezierDesigner->update();
}

void MainPanel::OpenFile()
{
    try {
        shapeCollection.clear();
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open"), "/home");
        shapeCollection.load(fileName.toStdString().c_str());
        bezierDesigner->update();
    } catch (const char* error) {
        QMessageBox msgBox(this);
        msgBox.setText(error);
        msgBox.exec();
    }
}

