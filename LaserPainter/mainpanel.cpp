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

bool ifFileExists(std::string fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}

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
    pointsInput->setValue(configuration.resolution);
    auto* repeatsLabel = new QLabel("Repeats" ,this);
    repeatsInput = new QSpinBox(this);
    repeatsInput->setRange(10, 5000);
    repeatsInput->setValue(configuration.repeats);

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

    if(ifFileExists(configuration.file))
    {
        shapeCollection.load(configuration.file.c_str());
    }

    if(!configuration.GetErrors().empty())
    {
        QMessageBox msgBox(this);
        msgBox.setText(QString(configuration.GetErrors().c_str()));
        msgBox.exec();
    }
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
    displayThread = new std::thread(&MainPanel::draw, this);
    startButton -> setText("Stop");
}

void MainPanel::draw()
{
    connector->draw(shapeCollection, pointsInput->value(), repeatsInput->value());
    startButton -> setText("Start");
}

void MainPanel::SaveFiel()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save"), configuration.dir.c_str());
    shapeCollection.save(fileName.toStdString().c_str());
}

void MainPanel::Clear()
{
    if(shapeCollection.points.size() > 0)
    {
        QMessageBox msgBox(this);
        msgBox.setInformativeText("Do you want to clear all points?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        int ret = msgBox.exec();
        if(ret == QMessageBox::Yes)
        {
            shapeCollection.clear();
            bezierDesigner->update();
        }
    }
}

void MainPanel::OpenFile()
{
    try {
        shapeCollection.clear();
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open"), QString(configuration.dir.c_str()));
        if(fileName.size() > 0)
        {
            std::string selectedFile = fileName.toStdString();
            shapeCollection.load(selectedFile.c_str());
            configuration.dir = selectedFile.substr(0, selectedFile.rfind('/'));
            configuration.file = selectedFile;
            bezierDesigner->update();
        }
    } catch (const char* error) {
        QMessageBox msgBox(this);
        msgBox.setText(error);
        msgBox.exec();
    }
}

