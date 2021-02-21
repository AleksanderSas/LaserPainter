#include "bezierdesigner.h"
#include "beziervisitor.h"
#include "bezier.h"
#include <QApplication>
#include <QPainter>
#include <QMouseEvent>
#include "math.h"

BezierDesigner::BezierDesigner(Bezier &bezier, QWidget *parent) : QFrame(parent), bezier(bezier)
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
    bezier.deletePoint(clickPointX * 4, clickPointY * 4);
    this->repaint();
}

void BezierDesigner::keyPressEvent(QKeyEvent * e)
{
    QWidget::keyPressEvent(e);
}
void BezierDesigner::mousePressEvent(QMouseEvent* e)
{
    if(e->button() == Qt::MouseButton::RightButton)
    {
        auto* bezierPoint = bezier.getPoint(e->x() * 4, e->y() * 4);
        delteAction->setEnabled(bezierPoint != nullptr);
        clickPointX = e->x();
        clickPointY = e->y();
        menu->popup(this->mapToGlobal(QPoint(e->x(), e->y())));
        return;
    }

    QWidget::mousePressEvent(e);
    selectedPoint = bezier.getOrAddPoint(e->x() * 4, e->y() * 4);
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
    if(bezier.curves.size() > 0)
    {
        Point p = bezier.curves[0];
        painter.drawEllipse((p.x - 3) / 4, (p.y - 3) / 4, 6, 6);

        for(unsigned int i = 1; i < bezier.curves.size(); i++)
        {
            Point &p1 = bezier.curves[i-1];
            Point &p2 = bezier.curves[i];
            painter.drawEllipse((p2.x - 3)/4, (p2.y - 3)/4, 6, 6);
            painter.drawLine(p2.x / 4, p2.y / 4, p1.x / 4, p1.y / 4);
        }
    }

    painter.setBrush(QBrush(Qt::red));
    if(selectedPoint != nullptr)
    {
        BezierVisitor bv(bezier, 300);
        const Point *pt;
        while((pt = bv.next()) != nullptr)
        {
            painter.drawPoint(pt->x / 4, pt->y / 4);
        }
    }

  }

