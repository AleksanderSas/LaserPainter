#ifndef BEZIERDESIGNER_H
#define BEZIERDESIGNER_H

#include <QFrame>
#include "shapecollection.h"
#include <QMenu>
#include <QComboBox>
#include <stack>
#include "abstractoperation.h"

class BezierDesigner : public QFrame
{
    Q_OBJECT
public:
    explicit BezierDesigner(ShapeCollection &sc, QComboBox *shapeSelector, QWidget *parent = nullptr);
    bool drawLines = true;

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);

signals:

public slots:
    void deletePoint();
    void switchLaser();
    void insertBezier();
    void insertCircle();
    void insertLine();
    void executeReDo();
    void executeUnDo();
    void setWait();

private:
    void addDo(AbstractOperation* op);
    void insert(ShapeType type);
    std::stack<AbstractOperation*> undo, redo;
    ShapeCollection &shapeCollection;
    QComboBox *shapeSelector;
    Point* selectedPoint = nullptr;
    bool isPointAdded;
    QMenu * menu;
    QAction *delteAction;
    QAction *switchLaserAction;
    QAction *insertBezierAction;
    QAction *insertLineAction;
    QAction *insertCircleAction;
    QAction *setWaitleAction;
    unsigned int clickPointX, clickPointY;
    void drawControlPoints(QPainter &painter);
    void drawLaserPath(QPainter &painter);
};

#endif // BEZIERDESIGNER_H
