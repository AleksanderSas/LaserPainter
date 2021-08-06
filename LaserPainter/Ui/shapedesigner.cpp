#include "shapedesigner.h"
#include "Visitors/beziervisitor.h"
#include <QApplication>
#include <QPainter>
#include <QMouseEvent>
#include "math.h"
#include "Collection//structs.h"
#include "Collection/adddeleteoperation.h"
#include "Collection/moveoperation.h"

#define MAX_W 1024
#define MAX_H 780

ShapeDesigner::ShapeDesigner(ShapeCollection &sc, QComboBox *shapeSelector, UnReDoPanel *unredoPanle, OperationLayer layer, QWidget *parent) :
    QFrame(parent),
    unredoPanle(unredoPanle),
    shapeCollection(sc),
    shapeSelector(shapeSelector),
    layer(layer)
{
    menu = new QMenu(this);
    delteAction = new QAction("Delete", this);
    switchLaserAction = new QAction("Disable Laser", this);
    insertBezierAction = new QAction("Insert Bezier", this);
    insertLineAction = new QAction("Insert Line", this);
    insertCircleAction = new QAction("Insert Circle", this);
    setWaitleAction = new QAction("Set wait", this);
    menu->addAction(delteAction);
    menu->addAction(switchLaserAction);
    menu->addAction(insertBezierAction);
    menu->addAction(insertLineAction);
    menu->addAction(insertCircleAction);
    menu->addAction(setWaitleAction);

    connect(delteAction, SIGNAL(triggered()), this, SLOT(deletePoint()));
    connect(switchLaserAction, SIGNAL(triggered()), this, SLOT(switchLaser()));
    connect(insertBezierAction, SIGNAL(triggered()), this, SLOT(insertBezier()));
    connect(insertCircleAction, SIGNAL(triggered()), this, SLOT(insertCircle()));
    connect(insertLineAction, SIGNAL(triggered()), this, SLOT(insertLine()));
    connect(setWaitleAction, SIGNAL(triggered()), this, SLOT(setWait()));

    this->setFixedSize(MAX_W, MAX_H);
    this->setFocusPolicy(Qt::ClickFocus);
}

void ShapeDesigner::insert(ShapeType type)
{
    Point p(clickPointX * 4, clickPointY * 4, type, true, false);
    shapeCollection.insertPointAfter(p);
    unredoPanle->addDo(new AddDeleteOperation(p), layer);
    this->repaint();
}

void ShapeDesigner::insertBezier()
{
    insert(ShapeType::BEZIER);
}

void ShapeDesigner::insertCircle()
{
    insert(ShapeType::CIRCLE);
}

void ShapeDesigner::insertLine()
{
    insert(ShapeType::LINE);
}

void ShapeDesigner::deletePoint()
{
    auto deleted = shapeCollection.deletePoint(clickPointX * 4, clickPointY * 4);
    unredoPanle->addDo(new AddDeleteOperation(deleted.second, deleted.first), layer);
    this->repaint();
}

void ShapeDesigner::switchLaser()
{
    auto* bezierPoint = shapeCollection.getPoint(clickPointX * 4, clickPointY * 4);
    bezierPoint->enableLaser = !bezierPoint->enableLaser;
    this->repaint();
}

void ShapeDesigner::setWait()
{
    auto* bezierPoint = shapeCollection.getPoint(clickPointX * 4, clickPointY * 4);
    bezierPoint->wait = !bezierPoint->wait;
    this->repaint();
}

ShapeType getShapeType(QString str)
{
    if(str == BEZIER_)
        return ShapeType::BEZIER;
    else if(str == LINE_)
        return ShapeType::LINE;
    else if(str == CIRCLE_)
        return ShapeType::CIRCLE;
}

int inline limit(int x, const int max)
{
    x = x > 0? x : 0;
    return x > max? max : x;
}

void ShapeDesigner::configureContextMenuButtons(point* selectedPoint)
{
    bool isExistingPointSelected = selectedPoint != nullptr;

    delteAction->setEnabled(isExistingPointSelected);
    switchLaserAction->setEnabled(isExistingPointSelected);
    setWaitleAction->setEnabled(isExistingPointSelected);
    if(isExistingPointSelected)
    {
        setWaitleAction->setText(selectedPoint->wait? "Disable wait" : "Enable wait");
        switchLaserAction->setText(selectedPoint->enableLaser? "Disable Laser" : "Enable Laser");
    }
}

void ShapeDesigner::keyPressEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_Escape)
    {
        selectionManager.clear();
        this->repaint();
    }
}

void ShapeDesigner::mousePressEvent(QMouseEvent* e)
{
    clickPointX = limit(e->x(), MAX_W - 5);
    clickPointY = limit(e->y(), MAX_H - 5);

    Qt::KeyboardModifiers modifier = QApplication::queryKeyboardModifiers();
    if(selectionManager.onMousePress(shapeCollection, clickPointX, clickPointY, modifier))
    {
        this->repaint();
        return;
    }

    if(e->button() == Qt::MouseButton::RightButton)
    {
        auto* bezierPoint = shapeCollection.getPoint(clickPointX * 4, clickPointY * 4);
        configureContextMenuButtons(bezierPoint);
        menu->popup(this->mapToGlobal(QPoint(clickPointX, clickPointY)));
        return;
    }

    ShapeType type = getShapeType(shapeSelector->currentText());
    QWidget::mousePressEvent(e);
    auto operationResult = shapeCollection.getOrAddPoint(clickPointX * 4, clickPointY * 4, type);
    selectedPoint = operationResult.second;
    isPointAdded = operationResult.first;
    this->repaint();
}

void ShapeDesigner::mouseReleaseEvent(QMouseEvent *e)
{    
    if(selectionManager.onMouseRelease(unredoPanle, layer));
    {
        this->repaint();
    }

    if(selectedPoint != nullptr && e->button() == Qt::MouseButton::LeftButton)
    {
        AbstractOperation* operation = isPointAdded
                ? (AbstractOperation*) new AddDeleteOperation(*selectedPoint)
                : new MoveOperation(*selectedPoint, clickPointX * 4, clickPointY * 4);
        unredoPanle->addDo(operation, layer);
    }
    selectedPoint = nullptr;
}

void ShapeDesigner::mouseMoveEvent(QMouseEvent *e)
{
    int x = limit(e->x(), MAX_W - 5);
    int y = limit(e->y(), MAX_H - 5);

    if(selectionManager.onMouseMove(x, y, shapeCollection))
    {
        this->repaint();
        return;
    }

    if(selectedPoint != nullptr)
    {
        selectedPoint->x = x * 4;
        selectedPoint->y = y * 4;
        this->repaint();
    }
}

void ShapeDesigner::paintEvent(QPaintEvent *e) {
    Q_UNUSED(e);

    QPainter painter(this);

    selectionManager.drawSelectionRectangle(painter);

    painter.setBrush(QBrush(Qt::darkBlue));
    drawControlPoints(painter);

    painter.setBrush(QBrush(Qt::red));
    drawLaserPath(painter);
}

Qt::GlobalColor ShapeDesigner::getControlPointColor(Point &p)
{
    if(selectionManager.isPOintSelected(&p))
    {
        return Qt::darkGreen;
    }
    return p.enableLaser? Qt::red : Qt::green;
}

void ShapeDesigner::drawControlPoints(QPainter &painter)
{
    if(shapeCollection.points.size() > 0)
    {
        for(unsigned int i = 0; i < shapeCollection.points.size() - 1; i++)
        {
            Point &p1 = shapeCollection.points[i];
            Point &p2 = shapeCollection.points[i+1];
            painter.setBrush(QBrush(getControlPointColor(p1)));
            int circleSize = p1.wait? 10 : 6;
            painter.drawEllipse((p1.x - 3)/4, (p1.y - 3)/4, circleSize, circleSize);
            if(drawLines)
            {
                painter.drawLine(p2.x / 4, p2.y / 4, p1.x / 4, p1.y / 4);
            }
        }

        Point &p = shapeCollection.points[shapeCollection.points.size() - 1];
        painter.setBrush(QBrush(getControlPointColor(p)));
        painter.drawEllipse((p.x - 3) / 4, (p.y - 3) / 4, 6, 6);
    }
}

void ShapeDesigner::drawLaserPath(QPainter &painter)
{
    const PointWithMetadata *pt;
    while((pt = shapeCollection.next(30)) != nullptr)
    {
        painter.drawPoint(pt->point.x / 4, pt->point.y / 4);
    }
}

