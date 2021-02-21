#ifndef BEZIERDESIGNER_H
#define BEZIERDESIGNER_H

#include <QFrame>
#include <vector>
#include "bezier.h"
#include <QMenu>

class BezierDesigner : public QFrame
{
    Q_OBJECT
public:
    explicit BezierDesigner(Bezier &bezier, QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent * e);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);
    void doPainting();

signals:

public slots:
    void deletePoint();
private:
    Bezier &bezier;
    Point* selectedPoint = nullptr;
    QMenu * menu;
    QAction *delteAction;
    QAction *insertAction;
    unsigned int clickPointX, clickPointY;
};

#endif // BEZIERDESIGNER_H
