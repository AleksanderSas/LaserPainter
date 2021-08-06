#include "multipleselectionmanager.h"
#include "../Collection/multiplemoveoperation.h"

MultipleSelectionManager::MultipleSelectionManager()
{
}

bool MultipleSelectionManager::onMousePress(ShapeCollection &shapeCollection, int x, int y, Qt::KeyboardModifiers modifier)
{
    selectedManyStartX = selectedManyEndX = x;
    selectedManyStartY = selectedManyEndY = y;
    if(modifier == Qt::NoModifier)
    {
        if(selectManyMode != SelectedManyMode::no && isCloseToAnySelected(x * 4, y * 4))
        {
            selectManyMode = SelectedManyMode::moving;
            return true;
        }
    }

    if(modifier == Qt::ShiftModifier)
    {
        selectManyMode = SelectedManyMode::selecting;
        return true;
    }

    if(modifier == Qt::ControlModifier)
    {
        Point* selectedPoint = shapeCollection.getPoint(x * 4, y * 4);
        selectManyMode = SelectedManyMode::selecting_ctrl;
        if(selectedPoints.find(selectedPoint) == selectedPoints.end())
        {
            selectedPoints.insert(selectedPoint);
        }
        else
        {
            selectedPoints.erase(selectedPoint);
        }
        return true;
    }
    else
    {
        selectManyMode = SelectedManyMode::no;
        selectedPoints.clear();
    }

    return false;
}

bool MultipleSelectionManager::onMouseRelease(UnReDoPanel *unredoPanle, OperationLayer layer)
{
    if(selectManyMode == SelectedManyMode::moving && (selectedManyStartX != selectedManyEndX || selectedManyStartY != selectedManyEndY))
    {
        unredoPanle->addDo(new MultipleMoveOperation(selectedPoints, (selectedManyEndX - selectedManyStartX) * 4, (selectedManyEndY - selectedManyStartY) * 4), layer);
        return true;
    }

    if(selectManyMode == SelectedManyMode::selecting)
    {
        selectedPoints.insert(selectedPointCondidates.begin(), selectedPointCondidates.end());
        selectedPointCondidates.clear();
        selectManyMode = SelectedManyMode::moving;
        return true;
    }

    return false;
}

bool MultipleSelectionManager::onMouseMove(int x, int y, ShapeCollection &shapeCollection)
{
    if(selectManyMode == SelectedManyMode::selecting)
    {
        selectedPointCondidates.clear();
        for(auto &p : shapeCollection.points)
        {
            if(isInsideSelectedArea(p.x / 4, p.y / 4))
            {
                selectedPointCondidates.insert(&p);
            }
        }
        selectedManyEndX = x;
        selectedManyEndY = y;

        return true;
    }

    if(selectManyMode == SelectedManyMode::moving)
    {
        int dx = x - selectedManyEndX;
        int dy = y - selectedManyEndY;
        for (auto point : selectedPoints)
        {
            point->x += dx * 4;
            point->y += dy * 4;
        }
        selectedManyEndX = x;
        selectedManyEndY = y;
        return true;
    }
    return false;
}

void MultipleSelectionManager::clear()
{
    selectedPointCondidates.clear();
    selectedPoints.clear();
}

void MultipleSelectionManager::drawSelectionRectangle(QPainter &painter)
{
    if(selectManyMode == SelectedManyMode::selecting)
    {
        painter.drawRect(selectedManyStartX, selectedManyStartY, selectedManyEndX - selectedManyStartX, selectedManyEndY - selectedManyStartY);
    }
}

bool MultipleSelectionManager::isPOintSelected(Point *p)
{
    return selectedPoints.find(p) != selectedPoints.end() || selectedPointCondidates.find(p) != selectedPointCondidates.end();
}

inline bool myXor(bool x, bool y){ return x != y; }

bool MultipleSelectionManager::isInsideSelectedArea(int x, int y)
{
    return myXor(x > selectedManyStartX, x > selectedManyEndX) && myXor(y > selectedManyStartY, y > selectedManyEndY);
}

bool MultipleSelectionManager::isCloseToAnySelected(int x, int y)
{
    for(auto &p: selectedPoints)
    {
        unsigned int dist = (p->x - x) * (p->x - x) + (p->y - y) * (p->y - y);
        if(dist < 2500)
        {
            return true;
        }
    }
    return false;
}
