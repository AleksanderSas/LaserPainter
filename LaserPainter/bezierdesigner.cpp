#include "bezierdesigner.h"
#include "beziervisitor.h"
#include <QApplication>
#include <QPainter>
#include <QMouseEvent>
#include "math.h"
#include "structs.h"

BezierDesigner::BezierDesigner(ShapeCollection &sc, QComboBox *shapeSelector, QWidget *parent) :
    QFrame(parent),
    shapeCollection(sc),
    shapeSelector(shapeSelector)
{
    menu = new QMenu(this);
    delteAction = new QAction("Delete", this);
    insertAction = new QAction("Insert", this);
    menu->addAction(delteAction);
    menu->addAction(insertAction);
    connect(delteAction, SIGNAL(triggered()), this, SLOT(deletePoint()));


    setStyleSheet("border: 1px solid red");
    this->setFixedSize(1024, 780);
}

void BezierDesigner::deletePoint()
{
    shapeCollection.deletePoint(clickPointX * 4, clickPointY * 4);
    this->repaint();
}

void BezierDesigner::keyPressEvent(QKeyEvent * e)
{
    QWidget::keyPressEvent(e);
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

void BezierDesigner::mousePressEvent(QMouseEvent* e)
{
    if(e->button() == Qt::MouseButton::RightButton)
    {
        auto* bezierPoint = shapeCollection.getPoint(e->x() * 4, e->y() * 4);
        delteAction->setEnabled(bezierPoint != nullptr);
        clickPointX = e->x();
        clickPointY = e->y();
        menu->popup(this->mapToGlobal(QPoint(e->x(), e->y())));
        return;
    }

    ShapeType type = getShapeType(shapeSelector->currentText());
    QWidget::mousePressEvent(e);
    selectedPoint = shapeCollection.getOrAddPoint(e->x() * 4, e->y() * 4, type);
    this->repaint();
}

void BezierDesigner::mouseReleaseEvent(QMouseEvent *e)
{
    selectedPoint = nullptr;
}

void BezierDesigner::mouseMoveEvent(QMouseEvent *e)
{
    if(selectedPoint != nullptr)
    {
        selectedPoint->x = e->x() * 4;
        selectedPoint->y = e->y() * 4;
        this->repaint();
    }
}

void BezierDesigner::paintEvent(QPaintEvent *e) {
    Q_UNUSED(e);

    doPainting();
  }

  void BezierDesigner::doPainting() {

    QPainter painter(this);

    painter.setBrush(QBrush(Qt::darkBlue));
    if(shapeCollection.points.size() > 0)
    {
        Point p = shapeCollection.points[0];
        painter.drawEllipse((p.x - 3) / 4, (p.y - 3) / 4, 6, 6);

        for(unsigned int i = 1; i < shapeCollection.points.size(); i++)
        {
            Point &p1 = shapeCollection.points[i-1];
            Point &p2 = shapeCollection.points[i];
            painter.drawEllipse((p2.x - 3)/4, (p2.y - 3)/4, 6, 6);
            painter.drawLine(p2.x / 4, p2.y / 4, p1.x / 4, p1.y / 4);
        }
    }

    painter.setBrush(QBrush(Qt::red));
    if(selectedPoint != nullptr)
    {
        const Point *pt;
        while((pt = shapeCollection.next(700)) != nullptr)
        {
            painter.drawPoint(pt->x / 4, pt->y / 4);
        }
    }

  }

