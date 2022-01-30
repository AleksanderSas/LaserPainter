#include "multipleselectionmanager.h"
#include "../Collection/multiplemoveoperation.h"
#include "../Collection/scaleoperation.h"
#include "CoordinateTransformation.h"

MultipleSelectionManager::MultipleSelectionManager()
{
}

bool MultipleSelectionManager::onMousePress(ShapeCollection &shapeCollection, int x, int y, Qt::KeyboardModifiers modifier)
{
    if(modifier == Qt::NoModifier && isRectangleCorner(x, y) && selectManyMode != SelectedManyMode::no)
    {
        selectManyMode = SelectedManyMode::scaling;
        originalScaling.clear();
        for(Point* p: selectedPointCondidates)
        {
            originalScaling.push_back(*p);
        }
        return true;
    }

    rectangleStartX = rectangleEndX = selectedManyStartX = selectedManyEndX = x;
    rectangleStartY = rectangleEndY = selectedManyStartY = selectedManyEndY = y;
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

    if(selectManyMode == SelectedManyMode::scaling)
    {
        unredoPanle->addDo(new ScaleOperation(selectedPoints, originalScaling), layer);
    }


    if(selectManyMode == SelectedManyMode::selecting)
    {
        selectedPoints.insert(selectedPointCondidates.begin(), selectedPointCondidates.end());
        selectManyMode = SelectedManyMode::moving_or_scaling;
        return true;
    }
    selectedManyStartX = rectangleStartX;
    selectedManyStartY = rectangleStartY;
    selectedManyEndX = rectangleEndX;
    selectedManyEndY = rectangleEndY;

    return false;
}

void MultipleSelectionManager::scalePoints(float scaleX, float scaleY, int anchoreX, int anchoreY)
{
    auto anchor = toCollectionPoint2(anchoreX, anchoreY);
    anchoreX = anchor.first;
    anchoreY = anchor.second;
    auto original = originalScaling.begin();
    for(auto &p : selectedPointCondidates)
    {
        Point& originalVal = *original;
        p->x = anchoreX - (anchoreX - originalVal.x) * scaleX;
        p->y = anchoreY - (anchoreY - originalVal.y) * scaleY;
        original++;
    }
}

void MultipleSelectionManager::scale(int x, int y)
{
    float xScale = 1.0f;
    float yScale = 1.0f;

    switch (scalingPoint) {
    case ScalingPoint::start_start:
        rectangleStartX = x;
        rectangleStartY = y;
        xScale = 1.0f * (selectedManyEndX - x ) / (selectedManyEndX - selectedManyStartX);
        yScale = 1.0f * (selectedManyEndY - y ) / (selectedManyEndY - selectedManyStartY);
        scalePoints(xScale, yScale, selectedManyEndX, selectedManyEndY);
        break;

    case ScalingPoint::start_end:
        rectangleStartX = x;
        rectangleEndY = y;
        xScale = 1.0f * (selectedManyEndX - x ) / (selectedManyEndX - selectedManyStartX);
        yScale = 1.0f * (y - selectedManyStartY ) / (selectedManyEndY - selectedManyStartY);
        scalePoints(xScale, yScale, selectedManyEndX, selectedManyStartY);
        break;

    case ScalingPoint::end_start:
        rectangleEndX = x;
        rectangleStartY = y;
        xScale = 1.0f * (x - selectedManyStartX) / (selectedManyEndX - selectedManyStartX);
        yScale = 1.0f * (selectedManyEndY - y ) / (selectedManyEndY - selectedManyStartY);
        scalePoints(xScale, yScale, selectedManyStartX, selectedManyEndY);
        break;

    case ScalingPoint::end_end:
        rectangleEndX = x;
        rectangleEndY = y;
        xScale = 1.0f * (x - selectedManyStartX) / (selectedManyEndX - selectedManyStartX);
        yScale = 1.0f * (y - selectedManyStartY ) / (selectedManyEndY - selectedManyStartY);
        scalePoints(xScale, yScale, selectedManyStartX, selectedManyStartY);
        break;
    }
}

bool MultipleSelectionManager::onMouseMove(int x, int y, ShapeCollection &shapeCollection)
{
    if(selectManyMode == SelectedManyMode::scaling)
    {
        scale(x, y);
        return true;
    }

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
        rectangleEndX = selectedManyEndX = x;
        rectangleEndY = selectedManyEndY = y;

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
        rectangleEndX = selectedManyEndX = x;
        rectangleEndY = selectedManyEndY = y;
        return true;
    }
    return false;
}

void MultipleSelectionManager::clear()
{
    selectedPointCondidates.clear();
    selectedPoints.clear();
    rectangleStartX = rectangleEndX = selectedManyStartX = selectedManyEndX =  -100;
    rectangleStartY = rectangleEndY = selectedManyStartY = selectedManyEndY = -100;
}

void MultipleSelectionManager::drawSelectionRectangle(QPainter &painter)
{
    if(selectManyMode == SelectedManyMode::selecting || selectManyMode == SelectedManyMode::scaling || selectManyMode == SelectedManyMode::moving_or_scaling)
    {
        painter.drawRect(rectangleStartX, rectangleStartY, rectangleEndX - rectangleStartX, rectangleEndY- rectangleStartY);
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

bool inline isClose(int x1, int y1, int x2, int y2)
{
    int dist = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
    return dist < 2500;
}

bool MultipleSelectionManager::isRectangleCorner(int x, int y)
{
    if(isClose(selectedManyStartX, selectedManyStartY, x, y))
    {
        scalingPoint = ScalingPoint::start_start;
        return true;
    }
    if(isClose(selectedManyStartX, selectedManyEndY, x, y))
    {
        scalingPoint = ScalingPoint::start_end;
        return true;
    }
    if(isClose(selectedManyEndX, selectedManyStartY, x, y))
    {
        scalingPoint = ScalingPoint::end_start;
        return true;
    }
    if(isClose(selectedManyEndX, selectedManyEndY, x, y))
    {
        scalingPoint = ScalingPoint::end_end;
        return true;
    }
    return false;
}

bool MultipleSelectionManager::isCloseToAnySelected(int x, int y)
{
    for(auto &p: selectedPoints)
    {
        if(isClose(p->x, p->y, x, y))
        {
            return true;
        }
    }
    return false;
}
