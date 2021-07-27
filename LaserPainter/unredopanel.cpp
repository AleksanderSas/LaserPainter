#include "unredopanel.h"
#include <QHBoxLayout>
#include <QShortcut>
#include <QStyle>

UnReDoPanel::UnReDoPanel(QWidget *panelToRepaint, ShapeCollection &sc, QWidget *parent):
    QFrame(parent),
    panelToRepaint(panelToRepaint),
    shapeCollection(sc)
{
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

void UnReDoPanel::addDo(AbstractOperation* operation)
{
    undo.push(operation);
    while (!redo.empty())
    {
        redo.pop();
    }
    unDoButton->setEnabled(true);
    reDoButton->setEnabled(false);
}

void UnReDoPanel::executeReDo()
{
    if(redo.size() > 0)
    {
        AbstractOperation* operation = redo.top();
        redo.pop();
        operation->reDo(shapeCollection);
        undo.push(operation);
    }
    unDoButton->setEnabled(true);
    reDoButton->setEnabled(redo.size() > 0);
    panelToRepaint->repaint();
}

void UnReDoPanel::executeUnDo()
{
    if(undo.size() > 0)
    {
        AbstractOperation* operation = undo.top();
        undo.pop();
        operation->unDo(shapeCollection);
        redo.push(operation);
    }
    unDoButton->setEnabled(undo.size() > 0);
    reDoButton->setEnabled(true);
    panelToRepaint->repaint();
}
