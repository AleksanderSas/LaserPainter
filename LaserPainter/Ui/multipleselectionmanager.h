#ifndef MULTIPLESELECTIONMANAGER_H
#define MULTIPLESELECTIONMANAGER_H

#include <set>
#include <QPainter>
#include "../Collection/shapecollection.h"

enum SelectedManyMode{ no, selecting, selecting_ctrl, moving};

class MultipleSelectionManager
{
public:
    MultipleSelectionManager();

    bool onMouseMove(int x, int y, ShapeCollection &shapeCollection);
    bool onMouseRelease();
    bool onMousePress(ShapeCollection &shapeCollection, int x, int y, Qt::KeyboardModifiers modifier);
    bool isPOintSelected(Point *p);
    void drawSelectionRectangle(QPainter &painter);

private:
    int selectedManyStartX, selectedManyStartY, selectedManyEndX, selectedManyEndY;
    SelectedManyMode selectManyMode = SelectedManyMode::no;
    std::set<Point*> selectedPoints;
    std::set<Point*> selectedPointCondidates;

    bool isCloseToAnySelected(int x, int y);
    bool isInsideSelectedArea(int x, int y);
};

#endif // MULTIPLESELECTIONMANAGER_H
