#include "multipleselectionmanager.h"
#include "../Collection/multiplemoveoperation.h"
#include "CoordinateTransformation.h"

MultipleSelectionManager::MultipleSelectionManager()
{
}

bool MultipleSelectionManager::onMousePress(ShapeCollection &shapeCollection, int x, int y, Qt::KeyboardModifiers modifier)
{
    selectedManyStartX = selectedManyEndX = x;
    selectedManyStartY = selectedManyEndY = y;
    auto cord = toCollectionPoint2(x, y);
    if(modifier == Qt::NoModifier)
    {
        if(selectManyMode != SelectedManyMode::no && isCloseToAnySelected(cord.first, cord.second))
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
        Point* selectedPoint = shapeCollection.getPoint(cord.first, cord.second);
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
        auto cord = scaleToCollection(selectedManyEndX - selectedManyStartX, selectedManyEndY - selectedManyStartY);
        unredoPanle->addDo(new MultipleMoveOperation(selectedPoints, cord.first, cord.second), layer);
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
            auto cord = fromCollectionPoint(p);
            if(isInsideSelectedArea(cord.first, cord.second))
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
        auto cord = scaleToCollection(x - selectedManyEndX, y - selectedManyEndY);
        for (auto point : selectedPoints)
        {
            point->x += cord.first;
            point->y += cord.second;
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

bool MultipleSelectionManager::isPointSelected(Point *p)
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
