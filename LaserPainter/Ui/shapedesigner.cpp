#include "shapedesigner.h"
#include "Visitors/beziervisitor.h"
#include <QApplication>
#include <QPainter>
#include <QMouseEvent>
#include "math.h"
#include "Collection//structs.h"
#include "Collection/adddeleteoperation.h"
#include "Collection/moveoperation.h"
#include "CoordinateTransformation.h"
#include "../mathutils.h"

#define MAX_W 1024
#define MAX_H 780

ShapeDesigner::ShapeDesigner(ShapeCollection &sc, QComboBox *shapeSelector, UnReDoPanel *unredoPanle, OperationLayer layer, StatusPanel *statusPanel, QWidget *parent) :
    QFrame(parent),
    unredoPanle(unredoPanle),
    shapeCollection(sc),
    shapeSelector(shapeSelector),
    statusPanel(statusPanel),
    layer(layer)
{
    menu = new QMenu(this);
    delteAction = new QAction("Delete", this);
    switchLaserAction = new QAction("Disable Laser", this);
    insertBezierAction = new QAction("Insert Bezier (after)", this);
    insertLineAction = new QAction("Insert Line after (after)", this);
    insertCircleAction = new QAction("Insert Circle (after)", this);
    insertHalfCircleAction = new QAction("Insert Half Circle (after)", this);
    setWaitleAction = new QAction("Set wait", this);
    menu->addAction(delteAction);
    menu->addAction(switchLaserAction);
    menu->addAction(insertBezierAction);
    menu->addAction(insertLineAction);
    menu->addAction(insertCircleAction);
    menu->addAction(insertHalfCircleAction);
    menu->addAction(setWaitleAction);

    connect(delteAction, SIGNAL(triggered()), this, SLOT(deletePoint()));
    connect(switchLaserAction, SIGNAL(triggered()), this, SLOT(switchLaser()));
    connect(insertBezierAction, SIGNAL(triggered()), this, SLOT(insertBezier()));
    connect(insertCircleAction, SIGNAL(triggered()), this, SLOT(insertCircle()));
    connect(insertHalfCircleAction, SIGNAL(triggered()), this, SLOT(insertHalfCircle()));
    connect(insertLineAction, SIGNAL(triggered()), this, SLOT(insertLine()));
    connect(setWaitleAction, SIGNAL(triggered()), this, SLOT(setWait()));

    this->setFixedSize(MAX_W, MAX_H);
    this->setFocusPolicy(Qt::ClickFocus);
}

std::pair<int,int> ShapeDesigner::toCollectionPoint()
{
    return toCollectionPoint2(clickPointX, clickPointY);
}

void ShapeDesigner::insert(ShapeType type)
{
    auto cord = toCollectionPoint();
    Point p(cord.first, cord.second, type, true, false);
    shapeCollection.insertPointAfter(p);
    unredoPanle->addDo(new AddDeleteOperation(p), layer);
    this->repaint();

    int invalidPointIdx = shapeCollection.validate();
    statusPanel->setValidation(invalidPointIdx);
}

void ShapeDesigner::insertBezier()
{
    insert(ShapeType::BEZIER);
}

void ShapeDesigner::insertCircle()
{
    insert(ShapeType::CIRCLE);
}

void ShapeDesigner::insertHalfCircle()
{
    insert(ShapeType::HALF_CIRCLE);
}

void ShapeDesigner::insertLine()
{
    insert(ShapeType::LINE);
}

void ShapeDesigner::deletePoint()
{
    auto cord = toCollectionPoint();
    auto deleted = shapeCollection.deletePoint(cord.first, cord.second);
    unredoPanle->addDo(new AddDeleteOperation(deleted.second, deleted.first), layer);
    statusPanel->setValidation(shapeCollection.validate());
    this->repaint();
}

void ShapeDesigner::switchLaser()
{
    auto cord = toCollectionPoint();
    auto* bezierPoint = shapeCollection.getPoint(cord.first, cord.second);
    bezierPoint->enableLaser = !bezierPoint->enableLaser;
    this->repaint();
}

void ShapeDesigner::setWait()
{
    auto cord = toCollectionPoint();
    auto* bezierPoint = shapeCollection.getPoint(cord.first, cord.second);
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
    else if(str == HALF_CIRCLE_)
        return ShapeType::HALF_CIRCLE;
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
        auto cord = toCollectionPoint();
        auto* bezierPoint = shapeCollection.getPoint(cord.first, cord.second);
        configureContextMenuButtons(bezierPoint);
        menu->popup(this->mapToGlobal(QPoint(clickPointX, clickPointY)));
        return;
    }

    ShapeType type = getShapeType(shapeSelector->currentText());
    QWidget::mousePressEvent(e);
    auto cord = toCollectionPoint();
    auto operationResult = shapeCollection.getOrAddPoint(cord.first, cord.second, type);
    selectedPoint = operationResult.second;
    isPointAdded = operationResult.first;

    if(isPointAdded)
    {
        int invalidPointIdx = shapeCollection.validate();
        statusPanel->setValidation(invalidPointIdx);
    }
    statusPanel->setPointInfo(selectedPoint);

    this->repaint();
}

void ShapeDesigner::mouseReleaseEvent(QMouseEvent *e)
{    
    if(selectionManager.onMouseRelease(unredoPanle, layer))
    {
        this->repaint();
    }

    if(selectedPoint != nullptr && e->button() == Qt::MouseButton::LeftButton)
    {
        auto cord = toCollectionPoint();
        AbstractOperation* operation = isPointAdded
                ? (AbstractOperation*) new AddDeleteOperation(*selectedPoint)
                : new MoveOperation(*selectedPoint, cord.first, cord.second);
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
        auto cord = toCollectionPoint2(x, y);
        selectedPoint->x = cord.first;
        selectedPoint->y = cord.second;
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
    if(selectionManager.isPointSelected(&p))
    {
        return Qt::darkGreen;
    }
    return p.enableLaser? Qt::red : Qt::green;
}

void ShapeDesigner::drawBackground(QPainter &painter)
{
    QPen p(QColor(235, 235, 235));
    p.setWidth(3);
    painter.setPen(p);

    painter.drawLine(0, MAX_H / 2, MAX_W, MAX_H / 2);
    painter.drawLine(MAX_W / 2, 0, MAX_W / 2, MAX_H);

    p.setStyle(Qt::PenStyle::DashLine);
    p.setWidth(1);
    painter.setPen(p);

    for(int i = -400; i <= 400; i += 200)
    {
        painter.drawLine(MAX_W / 2 + i, 0, MAX_W / 2 + i, MAX_H);
        painter.drawLine(0, MAX_H / 2 + i, MAX_W, MAX_H / 2 + i);
    }

    painter.setPen(QPen(Qt::black));
}

void ShapeDesigner::drawPoint(Point &p, QPainter &painter)
{
    painter.setBrush(QBrush(getControlPointColor(p)));
    auto cord = fromCollectionPoint(p);
    int circleSize = p.wait? 10 : 6;
    int shift = circleSize / 2;
    painter.drawEllipse(cord.first - shift, cord.second - shift, circleSize, circleSize);
}

void drawDirectionArrow(std::pair<int,int> &cord1, std::pair<int,int> &cord2, QPainter &painter)
{
    auto ortogonalVec = MathUtils::getNormalizedOrtogonal(cord1, cord2);
    auto normVec = MathUtils::getNormalizedVector(cord1, cord2);
    int arrowX = cord2.first + ortogonalVec.first * 10 + normVec.first * 20;
    int arrowY = cord2.second+ ortogonalVec.second * 10 + normVec.second * 20;
    painter.drawLine(arrowX, arrowY, cord2.first, cord2.second);
    painter.drawLine(arrowX, arrowY, cord2.first + normVec.first * 20, cord2.second + normVec.second * 20);
}

void drawLineWithArrow(QPainter &painter, std::pair<int,int> cord1, std::pair<int,int> cord2)
{
    painter.drawLine(cord2.first, cord2.second, cord1.first, cord1.second);
    if(MathUtils::squareDist(cord1, cord2) > 50 * 50)
    {
        drawDirectionArrow(cord1, cord2, painter);
    }
}

void drawArrowsForComponent(QPainter &painter, int idx,  ShapeCollection &collection)
{
    std::pair<unsigned int, unsigned int> poinRange = collection.getPointsFromComponent(idx);
    auto cord1 = fromCollectionPoint(collection.points[poinRange.first]);
    for(unsigned int i = poinRange.first + 1; i <= poinRange.second; i++)
    {
        auto cord2 = fromCollectionPoint(collection.points[i]);
        drawLineWithArrow(painter, cord1, cord2);
        cord1 = cord2;
    }
}

void ShapeDesigner::drawControlPoints(QPainter &painter)
{
    drawBackground(painter);

    if(shapeCollection.points.size() > 0)
    {
        for(unsigned int i = 0; i < shapeCollection.points.size() - 1; i++)
        {
            Point &p1 = shapeCollection.points[i];
            Point &p2 = shapeCollection.points[i+1];
            auto cord1 = fromCollectionPoint(p1);
            drawPoint(p1, painter);
            if(drawLines)
            {
                auto cord2 = fromCollectionPoint(p2);
                drawLineWithArrow(painter, cord1, cord2);
            }
            else
            {
                if(selectedPoint == &p1)
                {
                    drawArrowsForComponent(painter, i, shapeCollection);
                }
            }
        }

        Point &p = shapeCollection.points[shapeCollection.points.size() - 1];
        drawPoint(p, painter);
    }
}

void ShapeDesigner::drawLaserPath(QPainter &painter)
{    
    PointWithMetadata const *ptPrevious = shapeCollection.next(30, 0);
    if(ptPrevious == nullptr) return;
    auto cordPrevious = fromCollectionPoint(ptPrevious->point);
    PointWithMetadata const *ptCurrent = nullptr;

    QPen p(QColor(255, 130, 130));
    p.setWidth(1);
    painter.setPen(p);

    while((ptCurrent = shapeCollection.next(30, 0)) != nullptr)
    {
        auto cordCurrent = fromCollectionPoint(ptCurrent->point);
        if(drawShape)
        {
            painter.drawLine(cordPrevious.first, cordPrevious.second, cordCurrent.first, cordCurrent.second);
        }
        else
        {
            painter.drawPoint(cordCurrent.first, cordCurrent.second);
        }
        cordPrevious = cordCurrent;
    }
}

void ShapeDesigner::reset()
{
    selectionManager.clear();
    this->repaint();
}
