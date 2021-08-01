#include "mainpanel.h"
#include "shapedesigner.h"
#include "hardwareconnector.h"
#include "unredopanel.h"

#include <QFrame>
#include <QStatusBar>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFileDialog>
#include <thread>
#include <QMessageBox>
#include <QTimer>
#include <QTabWidget>

#include "math.h"

bool ifFileExists(std::string fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}

QSpinBox* MainPanel::CreateAndAddSpinner(char* title, int initValue, QVBoxLayout* layout)
{
    auto *spinner = new QSpinBox(this);
    spinner->setRange(1, 100);
    spinner->setValue(initValue);

    layout->addWidget(new QLabel(title ,this), 0, Qt::AlignTop);
    layout->addWidget(spinner, 0, Qt::AlignTop);
    layout->addStretch(2);

    return spinner;
}

MainPanel::MainPanel(QWidget *parent) : QWidget(parent)
{
    auto *hbox = new QHBoxLayout(this);
    auto *vbox = new QVBoxLayout();
    auto* shapeSelector = new QComboBox(this);
    auto* unrePanel = new UnReDoPanel(this, &project.shape, &project.move, this);
    shapeDesigner = new ShapeDesigner(project.shape, shapeSelector, unrePanel, OperationLayer::shape, this);
    moveDesigner = new ShapeDesigner(project.move, shapeSelector, unrePanel, OperationLayer::move, this);
    startButton = new QPushButton("Start", this);
    auto* clearButton = new QPushButton("Clear", this);
    auto* saveButton = new QPushButton("Save", this);
    auto* openButton = new QPushButton("Open", this);
    shapeSelector->addItems(QStringList{BEZIER_, LINE_, CIRCLE_});

    auto* repeatsLabel = new QLabel("Repeats" ,this);
    repeatsInput = new QSpinBox(this);
    repeatsInput->setRange(10, 5000);
    repeatsInput->setValue(configuration.repeats);

    drawLinesCheckbox = new QCheckBox("draw lines", this);
    drawLinesCheckbox->setChecked(true);

    scaleBar = new QScrollBar(Qt::Orientation::Horizontal, this);
    scaleBar->setRange(1, 100);
    scaleBar->setValue(configuration.scale);
    scaleLabel = new QLabel(QString("Scale: ") + QString::number(configuration.scale) + "%", this);
    enableWaitCircuid = new QCheckBox("wait circuid", this);

    vbox->setSpacing(5);
    vbox->addWidget(unrePanel, 0, Qt::AlignTop);
    vbox->setSpacing(5);
    vbox->addWidget(startButton, 0, Qt::AlignTop);
    vbox->addWidget(clearButton, 0, Qt::AlignTop);
    vbox->addWidget(saveButton, 0, Qt::AlignTop);
    vbox->addWidget(openButton, 0, Qt::AlignTop);
    vbox->addWidget(drawLinesCheckbox, 0, Qt::AlignTop);
    vbox->addWidget(enableWaitCircuid, 0, Qt::AlignTop);
    vbox->addStretch(5);
    vbox->addWidget(shapeSelector, 0, Qt::AlignTop);
    vbox->addStretch(5);

    moveSpeedInput = CreateAndAddSpinner("Move Speed", configuration.moveSpeed, vbox);
    pointsInput = CreateAndAddSpinner("Points", configuration.resolution, vbox);

    vbox->addWidget(repeatsLabel, 0, Qt::AlignTop);
    vbox->addWidget(repeatsInput, 0, Qt::AlignTop);
    vbox->addStretch(5);
    vbox->addWidget(scaleLabel, 0, Qt::AlignTop);
    vbox->addWidget(scaleBar, 0, Qt::AlignTop);
    vbox->addStretch(90);

    hbox->addItem(vbox);
    auto* tabWidget = new QTabWidget(this);
    tabWidget->addTab(shapeDesigner, "shape designer");
    tabWidget->addTab(moveDesigner, "move designer");
    hbox->addWidget(tabWidget, 5);

    connect(openButton, SIGNAL(clicked()), this, SLOT(openFile()));
    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveFile()));
    connect(clearButton, SIGNAL(clicked()), this, SLOT(clear()));
    connect(startButton, SIGNAL(clicked()), this, SLOT(hardwareDraw()));
    connect(drawLinesCheckbox, SIGNAL(clicked()), this, SLOT(lineChecbox()));
    connect(scaleBar, SIGNAL(valueChanged(int)), this, SLOT(scaleUpdated(int)));
    connect(tabWidget, SIGNAL(currentChanged(int)), unrePanel, SLOT(setMode(int)));

    connector = new HardwareConnector();

    if(ifFileExists(configuration.file))
    {
        project.load(configuration.file.c_str());
    }

    if(!configuration.GetErrors().empty())
    {
        QMessageBox msgBox(this);
        msgBox.setText(QString(configuration.GetErrors().c_str()));
        msgBox.exec();
    }
}

void MainPanel::updateConfiguration()
{
    configuration.resolution = static_cast<unsigned int>(pointsInput->value());
    configuration.repeats = static_cast<unsigned int>(repeatsInput->value());
    configuration.moveSpeed = static_cast<unsigned int>(moveSpeedInput->value());
    configuration.scale = static_cast<unsigned int>(scaleBar->value());
}

MainPanel::~MainPanel()
{
    updateConfiguration();
}

void MainPanel::scaleUpdated(int value)
{
    scaleLabel->setText(QString("Scale: ") + QString::number(value) + "%");
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

void MainPanel::lineChecbox()
{
    shapeDesigner->drawLines = drawLinesCheckbox->isChecked();
    shapeDesigner->update();
}

static const char* errorMessage;
static QTimer* timer;
void MainPanel::displayError()
{
    QMessageBox msgBox(this);
    msgBox.setInformativeText(QString(errorMessage));
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
    timer->deleteLater();
}

void MainPanel::draw()
{
    updateConfiguration();
    errorMessage = connector->draw(project, &configuration, enableWaitCircuid->checkState() == Qt::CheckState::Checked);
    if(errorMessage != nullptr)
    {
        // any thread
        timer = new QTimer();
        timer->moveToThread(this->thread());
        timer->setSingleShot(true);
        connect(timer, SIGNAL(timeout()), this, SLOT(displayError()));
        QMetaObject::invokeMethod(timer, "start", Qt::QueuedConnection, Q_ARG(int, 0));
    }
    startButton -> setText("Start");
}

void MainPanel::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save"), configuration.dir.c_str());
    project.save(fileName.toStdString().c_str());
}

void MainPanel::clear()
{
    if(project.isEmpty())
    {
        QMessageBox msgBox(this);
        msgBox.setInformativeText("Do you want to clear all points?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        int ret = msgBox.exec();
        if(ret == QMessageBox::Yes)
        {
            project.clear();
            shapeDesigner->update();
        }
    }
}

void MainPanel::openFile()
{
    try {
        project.clear();
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open"), QString(configuration.dir.c_str()));
        if(fileName.size() > 0)
        {
            std::string selectedFile = fileName.toStdString();
            project.load(selectedFile.c_str());
            configuration.dir = selectedFile.substr(0, selectedFile.rfind('/'));
            configuration.file = selectedFile;
            shapeDesigner->update();
        }
    } catch (const char* error) {
        QMessageBox msgBox(this);
        msgBox.setText(error);
        msgBox.exec();
    }
}

