#include "bezierdesigner.h"
#include "beziervisitor.h"
#include <QApplication>
#include <QPainter>
#include <QMouseEvent>
#include "math.h"
#include "structs.h"
#include "adddeleteoperation.h"
#include "moveoperation.h"

#define MAX_W 1024
#define MAX_H 780

BezierDesigner::BezierDesigner(ShapeCollection &sc, QComboBox *shapeSelector, UnReDoPanel *unredoPanle, QWidget *parent) :
    QFrame(parent),
    shapeCollection(sc),
    shapeSelector(shapeSelector),
    unredoPanle(unredoPanle)
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

    setStyleSheet("border: 1px solid red");
    this->setFixedSize(MAX_W, MAX_H);
}

void BezierDesigner::insert(ShapeType type)
{
    Point p(clickPointX * 4, clickPointY * 4, type, true, false);
    shapeCollection.insertPointAfter(p);
    unredoPanle->addDo(new AddDeleteOperation(p));
    this->repaint();
}

void BezierDesigner::insertBezier()
{
    insert(ShapeType::BEZIER);
}

void BezierDesigner::insertCircle()
{
    insert(ShapeType::CIRCLE);
}

void BezierDesigner::insertLine()
{
    insert(ShapeType::LINE);
}

void BezierDesigner::deletePoint()
{
    auto deleted = shapeCollection.deletePoint(clickPointX * 4, clickPointY * 4);
    unredoPanle->addDo(new AddDeleteOperation(deleted.second, deleted.first));
    this->repaint();
}

void BezierDesigner::switchLaser()
{
    auto* bezierPoint = shapeCollection.getPoint(clickPointX * 4, clickPointY * 4);
    bezierPoint->enableLaser = !bezierPoint->enableLaser;
    this->repaint();
}

void BezierDesigner::setWait()
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

void BezierDesigner::configureContextMenuButtons(point* selectedPoint)
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

void BezierDesigner::mousePressEvent(QMouseEvent* e)
{
    clickPointX = limit(e->x(), MAX_W - 5);
    clickPointY = limit(e->y(), MAX_H - 5);

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

void BezierDesigner::mouseReleaseEvent(QMouseEvent *e)
{
    if(selectedPoint != nullptr && e->button() == Qt::MouseButton::LeftButton)
    {
        AbstractOperation* operation = isPointAdded
                ? (AbstractOperation*) new AddDeleteOperation(*selectedPoint)
                : new MoveOperation(*selectedPoint, clickPointX * 4, clickPointY * 4);
        unredoPanle->addDo(operation);
    }
    selectedPoint = nullptr;
}

void BezierDesigner::mouseMoveEvent(QMouseEvent *e)
{
    if(selectedPoint != nullptr)
    {
        int x = limit(e->x(), MAX_W - 5);
        int y = limit(e->y(), MAX_H - 5);
        selectedPoint->x = x * 4;
        selectedPoint->y = y * 4;
        this->repaint();
    }
}

void BezierDesigner::paintEvent(QPaintEvent *e) {
    Q_UNUSED(e);

    QPainter painter(this);

    painter.setBrush(QBrush(Qt::darkBlue));
    drawControlPoints(painter);

    painter.setBrush(QBrush(Qt::red));
    drawLaserPath(painter);
  }

void BezierDesigner::drawControlPoints(QPainter &painter)
{
    if(shapeCollection.points.size() > 0)
    {
        for(unsigned int i = 0; i < shapeCollection.points.size() - 1; i++)
        {
            Point &p1 = shapeCollection.points[i];
            Point &p2 = shapeCollection.points[i+1];
            painter.setBrush(p1.enableLaser? QBrush(Qt::red) : QBrush(Qt::green));
            int circleSize = p1.wait? 10 : 6;
            painter.drawEllipse((p1.x - 3)/4, (p1.y - 3)/4, circleSize, circleSize);
            if(drawLines)
            {
                painter.drawLine(p2.x / 4, p2.y / 4, p1.x / 4, p1.y / 4);
            }
        }

        Point p = shapeCollection.points[shapeCollection.points.size() - 1];
        painter.setBrush(p.enableLaser? QBrush(Qt::red) : QBrush(Qt::green));
        painter.drawEllipse((p.x - 3) / 4, (p.y - 3) / 4, 6, 6);
    }
}

void BezierDesigner::drawLaserPath(QPainter &painter)
{
    const PointWithMetadata *pt;
    while((pt = shapeCollection.next(30)) != nullptr)
    {
        painter.drawPoint(pt->point.x / 4, pt->point.y / 4);
    }
}

