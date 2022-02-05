#ifndef BEZIERDESIGNER_H
#define BEZIERDESIGNER_H

#include <QFrame>
#include "Collection/shapecollection.h"
#include <QMenu>
#include <QComboBox>
#include "Collection/abstractoperation.h"
#include "unredopanel.h"
#include "multipleselectionmanager.h"
#include <tuple>
#include <QLabel>
#include "statuspanel.h"

class ShapeDesigner : public QFrame
{
    Q_OBJECT
public:
    explicit ShapeDesigner(ShapeCollection &sc, QComboBox *shapeSelector, UnReDoPanel *unredoPanle, OperationLayer layer, StatusPanel *statusPanel, QWidget *parent = nullptr);
    bool drawLines = true;
    bool drawShape = true;
    void reset();
    
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void paintEvent(QPaintEvent *e) override;
    void keyPressEvent(QKeyEvent* event) override;

signals:

public slots:
    void deletePoint();
    void switchLaser();
    void insertBezier();
    void insertCircle();
    void insertHalfCircle();
    void insertLine();
    void setWait();

private:
    std::pair<int,int> toCollectionPoint();

    MultipleSelectionManager selectionManager;
    UnReDoPanel *unredoPanle;
    void insert(ShapeType type);
    ShapeCollection &shapeCollection;
    QComboBox *shapeSelector;
    Point* selectedPoint = nullptr;
    StatusPanel *statusPanel;

    bool isPointAdded;
    QMenu * menu;
    QAction *delteAction;
    QAction *switchLaserAction;
    QAction *insertBezierAction;
    QAction *insertLineAction;
    QAction *insertCircleAction;
    QAction *insertHalfCircleAction;
    QAction *setWaitleAction;
    int clickPointX, clickPointY;
    void drawControlPoints(QPainter &painter);
    void drawBackground(QPainter &painter);
    void drawLaserPath(QPainter &painter);
    void configureContextMenuButtons(point* selectedPoint);
    Qt::GlobalColor getControlPointColor(Point &p);
    void drawPoint(Point &p, QPainter &painter);
    OperationLayer layer;
};

#endif // BEZIERDESIGNER_H
