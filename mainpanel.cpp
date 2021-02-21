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
    bezierDesigner = new BezierDesigner(bezier, this);
    startButton = new QPushButton("Start", this);
    auto* clearButton = new QPushButton("Clear", this);
    auto* saveButton = new QPushButton("Save", this);
    auto* openButton = new QPushButton("Open", this);

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
    vbox->addWidget(pointsLabel, 0, Qt::AlignTop);
    vbox->addWidget(pointsInput, 0, Qt::AlignTop);
    vbox->addWidget(repeatsLabel, 0, Qt::AlignTop);
    vbox->addWidget(repeatsInput, 0, Qt::AlignTop);
    vbox->addStretch();

    hbox->addItem(vbox);
    hbox->addWidget(bezierDesigner, 5);

    connect(openButton, SIGNAL(clicked()), this, SLOT(OpenFile()));
    connect(saveButton, SIGNAL(clicked()), this, SLOT(SaveFiel()));
    connect(clearButton, SIGNAL(clicked()), this, SLOT(Clear()));
    connect(startButton, SIGNAL(clicked()), this, SLOT(hardwareDraw()));
    drawHeard(bezier);

    connector = new HardwareConnector();
}

#define PI 3.1415
void kolo(Bezier& b, int x, int y, int r)
{
    const int n = 11;
    for(int i  = 0; i < n; i++)
    {
        b.Add(x + sin(PI * 2 * i / n) * r, y + cos(PI * 2 * i / n) * r);
    }
    b.Add(x, y + r);
}

void drawHeard(Bezier &b)
{

    //karoseria - przy przednim kole
    b.Add(1280, 2530);
    b.Add(730, 2500);
    b.Add(360, 2465);
    b.Add(340, 2430);
    b.Add(340, 2340);

    b.Add(325, 2275);
    b.Add(400, 2185);
    b.Add(750, 2080);
    b.Add(1225, 2030);

    //poczatek przedniej szyby
    b.Add(1260, 2010);
    b.Add(1480, 1900);
    b.Add(1755, 1805);
    b.Add(1815, 1795);

    //okna
    b.Add(2490, 1840);
    b.Add(2655, 1925);
    b.Add(2740, 2030);
    b.Add(2430, 2040);

    b.Add(1540, 2060);
    b.Add(1360, 2070);
    b.Add(1360, 2030);
    b.Add(1710, 1860);

    b.Add(1770, 1845);
    b.Add(1890, 1805);
    b.Add(2110, 1785);
    b.Add(2215, 1795);

    //poczatek tylnej szyby
    b.Add(2389, 1780);
    b.Add(2500, 1780);
    b.Add(3340, 1975);
    b.Add(3400, 1990);

    //bagaznik
    b.Add(3495, 1990);
    b.Add(3560, 2060);
    b.Add(3600, 2180);
    b.Add(3560, 2390);

    kolo(b, 2980, 2400, 240);

    //karoseria, tylna czesc tylnego zwisu
    b.Add(3330, 2415);
    b.Add(3190, 2510);
    b.Add(3030, 2500);
    b.Add(1280, 2530);

    kolo(b, 1000, 2400, 240);
}

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
    connector->drawBezier(bezier, pointsInput->value(), repeatsInput->value());
    startButton -> setText("Start");
}

void MainPanel::SaveFiel()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save"), "/home");
    bezier.save(fileName.toStdString().c_str());
}

void MainPanel::Clear()
{
    bezier.clear();
    bezierDesigner->update();
}

void MainPanel::OpenFile()
{
    try {
        bezier.clear();
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open"), "/home");
        bezier.load(fileName.toStdString().c_str());
        bezierDesigner->update();
    } catch (const char* error) {
        QMessageBox msgBox(this);
        msgBox.setText(error);
        msgBox.exec();
    }
}

