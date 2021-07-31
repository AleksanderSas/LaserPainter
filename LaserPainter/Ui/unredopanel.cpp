#include "unredopanel.h"
#include <QHBoxLayout>
#include <QShortcut>
#include <QStyle>

UnReDoPanel::UnReDoPanel(QWidget *panelToRepaint, ShapeCollection *sc1, ShapeCollection *sc2, QWidget *parent):
    QFrame(parent),
    panelToRepaint(panelToRepaint)
{
    shapeCollection[0] = sc1;
    shapeCollection[1] = sc2;
    auto *undoredoBox = new QHBoxLayout(this);
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

void UnReDoPanel::addDo(AbstractOperation* operation, int mode)
{
    undo[mode].push(operation);
    while (!redo[mode].empty())
    {
        redo[mode].pop();
    }
   updateButtons();
}

void UnReDoPanel::updateButtons()
{
    unDoButton->setEnabled(undo[mode].size() > 0);
    reDoButton->setEnabled(redo[mode].size() > 0);
}

void UnReDoPanel::executeReDo()
{
    if(redo[mode].size() > 0)
    {
        AbstractOperation* operation = redo[mode].top();
        redo[mode].pop();
        operation->reDo(*shapeCollection[mode]);
        undo[mode].push(operation);
    }
    updateButtons();
    panelToRepaint->repaint();
}

void UnReDoPanel::executeUnDo()
{
    if(undo[mode].size() > 0)
    {
        AbstractOperation* operation = undo[mode].top();
        undo[mode].pop();
        operation->unDo(*shapeCollection[mode]);
        redo[mode].push(operation);
    }
    updateButtons();
    panelToRepaint->repaint();
}

void UnReDoPanel::setMode(int mode)
{
    this->mode = mode;
    updateButtons();
}
