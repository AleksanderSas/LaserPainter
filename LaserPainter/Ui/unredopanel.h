#ifndef UNREDOPANEL_H
#define UNREDOPANEL_H

#include "Collection/abstractoperation.h"

#include <QWidget>
#include <QFrame>
#include <QPushButton>
#include <stack>
#include "statuspanel.h"

enum OperationLayer { shape, move };

class UnReDoPanel : public QWidget
{
    Q_OBJECT

public:
    UnReDoPanel(QWidget *panelToRepaint, ShapeCollection *sc1, ShapeCollection *sc2, StatusPanel* statusPanel, QWidget *parent = nullptr);
    void addDo(AbstractOperation* op, OperationLayer layer);
    void clear();

protected:

public slots:
    void executeUnDo();
    void executeReDo();
    void setMode(int mode);

private:
    StatusPanel* statusPanel;
    QPushButton *unDoButton;
    QPushButton *reDoButton;
    QWidget* panelToRepaint;
    ShapeCollection* shapeCollection[2];
    std::stack<AbstractOperation*> undo[2], redo[2];
    OperationLayer layer = OperationLayer::shape;
    void updateButtons();
    void clear(std::stack<AbstractOperation*> &set);
};

#endif // UNREDOPANEL_H
