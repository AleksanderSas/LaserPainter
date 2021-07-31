#ifndef BEZIERDESIGNER_H
#define BEZIERDESIGNER_H

#include <QFrame>
#include "Collection/shapecollection.h"
#include <QMenu>
#include <QComboBox>
#include "Collection/abstractoperation.h"
#include "unredopanel.h"

class ShapeDesigner : public QFrame
{
    Q_OBJECT
public:
    explicit ShapeDesigner(ShapeCollection &sc, QComboBox *shapeSelector, UnReDoPanel *unredoPanle, OperationLayer layer, QWidget *parent = nullptr);
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
    void setWait();

private:

    UnReDoPanel *unredoPanle;
    void insert(ShapeType type);
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
    void configureContextMenuButtons(point* selectedPoint);
    OperationLayer layer;
};

#endif // BEZIERDESIGNER_H
