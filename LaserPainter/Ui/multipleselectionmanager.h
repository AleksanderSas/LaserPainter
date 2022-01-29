#ifndef MULTIPLESELECTIONMANAGER_H
#define MULTIPLESELECTIONMANAGER_H

#include <set>
#include <vector>
#include <QPainter>
#include "../Collection/shapecollection.h"
#include "unredopanel.h"

enum SelectedManyMode{ no, selecting, selecting_ctrl, moving_or_scaling, moving, scaling};
enum ScalingPoint{ start_start, start_end, end_start, end_end};

class MultipleSelectionManager
{
public:
    MultipleSelectionManager();

    bool onMouseMove(int x, int y, ShapeCollection &shapeCollection);
    bool onMouseRelease(UnReDoPanel *unredoPanle, OperationLayer layer);
    bool onMousePress(ShapeCollection &shapeCollection, int x, int y, Qt::KeyboardModifiers modifier);
    bool isPointSelected(Point *p);
    void drawSelectionRectangle(QPainter &painter);
    void clear();

private:
    int selectedManyStartX, selectedManyStartY, selectedManyEndX, selectedManyEndY;
    int rectangleStartX, rectangleStartY, rectangleEndX, rectangleEndY;
    SelectedManyMode selectManyMode = SelectedManyMode::no;
    ScalingPoint scalingPoint;
    std::set<Point*> selectedPoints;
    std::set<Point*> selectedPointCondidates;
    std::vector<Point> originalScaling;
    void scale(int x, int y);
    void scalePoints(float scaleX, float scaleY, int anchoreX, int anchoreY);

    bool isRectangleCorner(int x, int y);
    bool isCloseToAnySelected(int x, int y);
    bool isInsideSelectedArea(int x, int y);
};

#endif // MULTIPLESELECTIONMANAGER_H
