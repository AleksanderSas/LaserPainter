#ifndef UNREDOPANEL_H
#define UNREDOPANEL_H

#include "Collection/abstractoperation.h"

#include <QWidget>
#include <QFrame>
#include <QPushButton>
#include <stack>


class UnReDoPanel : public QFrame
{
    Q_OBJECT

public:
    UnReDoPanel(QWidget *panelToRepaint, ShapeCollection &sc, QWidget *parent = nullptr);
    void addDo(AbstractOperation* op);

protected:

public slots:
    void executeUnDo();
    void executeReDo();

private:
    QPushButton *unDoButton;
    QPushButton *reDoButton;
    QWidget* panelToRepaint;
    ShapeCollection &shapeCollection;
    std::stack<AbstractOperation*> undo, redo;
};

#endif // UNREDOPANEL_H
