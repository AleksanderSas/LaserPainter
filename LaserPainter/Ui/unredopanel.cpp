#include "unredopanel.h"
#include <QHBoxLayout>
#include <QShortcut>
#include <QStyle>

UnReDoPanel::UnReDoPanel(QWidget *panelToRepaint, ShapeCollection *sc1, ShapeCollection *sc2, StatusPanel* statusPanel, QWidget *parent):
    QWidget(parent),
    statusPanel(statusPanel),
    panelToRepaint(panelToRepaint)
{
    shapeCollection[0] = sc1;
    shapeCollection[1] = sc2;
    auto *undoredoBox = new QHBoxLayout(this);
    undoredoBox->setContentsMargins(0, 0, 0, 0);
    unDoButton = new QPushButton(this);
    unDoButton->setIcon(style()->standardIcon(QStyle::SP_ArrowLeft));
    unDoButton->setEnabled(false);
    unDoButton->setToolTip("Undo Ctrl+Z");
    connect(unDoButton, SIGNAL(clicked()), this, SLOT(executeUnDo()));

    reDoButton = new QPushButton(this);
    reDoButton->setIcon(style()->standardIcon(QStyle::SP_ArrowRight));
    reDoButton->setEnabled(false);
    reDoButton->setToolTip("Redo Ctrl+Y");
    connect(reDoButton, SIGNAL(clicked()), this, SLOT(executeReDo()));

    undoredoBox->addWidget(unDoButton , 0, Qt::AlignTop);
    undoredoBox->setSpacing(5);
    undoredoBox->addWidget( reDoButton, 0, Qt::AlignTop);

    QShortcut* undoShortcut = new QShortcut(this);
    undoShortcut->setKey(Qt::CTRL + Qt::Key_Z);
    connect(undoShortcut, SIGNAL(activated()), this, SLOT(executeUnDo()));

    QShortcut* redoShortcut = new QShortcut(this);
    redoShortcut->setKey(Qt::CTRL + Qt::Key_Y);
    connect(redoShortcut, SIGNAL(activated()), this, SLOT(executeReDo()));
}

void UnReDoPanel::clear()
{
    clear(undo[OperationLayer::move]);
    clear(undo[OperationLayer::shape]);
    clear(redo[OperationLayer::move]);
    clear(redo[OperationLayer::shape]);
    updateButtons();
}

void UnReDoPanel::clear(std::stack<AbstractOperation*> &set)
{
    while (!set.empty())
    {
        auto op = set.top();
        set.pop();
        delete op;
    }
}

void UnReDoPanel::addDo(AbstractOperation* operation, OperationLayer layer)
{
    undo[layer].push(operation);
    clear(redo[layer]);
    updateButtons();
}

void UnReDoPanel::updateButtons()
{
    unDoButton->setEnabled(undo[layer].size() > 0);
    reDoButton->setEnabled(redo[layer].size() > 0);
}

void UnReDoPanel::executeReDo()
{
    if(redo[layer].size() > 0)
    {
        AbstractOperation* operation = redo[layer].top();
        redo[layer].pop();
        operation->reDo(*shapeCollection[layer]);
        undo[layer].push(operation);
    }
    updateButtons();
    int invalidPOintIdx = shapeCollection[layer]->validate();
    statusPanel->setValidation(invalidPOintIdx);
    panelToRepaint->repaint();
}

void UnReDoPanel::executeUnDo()
{
    if(undo[layer].size() > 0)
    {
        AbstractOperation* operation = undo[layer].top();
        undo[layer].pop();
        operation->unDo(*shapeCollection[layer]);
        redo[layer].push(operation);
    }
    updateButtons();
    int invalidPOintIdx = shapeCollection[layer]->validate();
    statusPanel->setValidation(invalidPOintIdx);
    panelToRepaint->repaint();
}

void UnReDoPanel::setMode(int layer)
{
    this->layer = static_cast<OperationLayer>(layer);
    updateButtons();
}
