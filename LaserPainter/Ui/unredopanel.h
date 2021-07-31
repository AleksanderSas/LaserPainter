#ifndef UNREDOPANEL_H
#define UNREDOPANEL_H

#include "Collection/abstractoperation.h"

#include <QWidget>
#include <QFrame>
#include <QPushButton>
#include <stack>

enum OperationLayer { shape, move };

class UnReDoPanel : public QFrame
{
    Q_OBJECT

public:
    UnReDoPanel(QWidget *panelToRepaint, ShapeCollection *sc1, ShapeCollection *sc2, QWidget *parent = nullptr);
    void addDo(AbstractOperation* op, OperationLayer layer);

protected:

public slots:
    void executeUnDo();
    void executeReDo();
    void setMode(int mode);

private:
    QPushButton *unDoButton;
    QPushButton *reDoButton;
    QWidget* panelToRepaint;
    ShapeCollection* shapeCollection[2];
    std::stack<AbstractOperation*> undo[2], redo[2];
    OperationLayer layer = OperationLayer::shape;
    void updateButtons();
};

#endif // UNREDOPANEL_H
