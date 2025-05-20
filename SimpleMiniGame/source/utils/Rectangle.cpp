#include "../../include/utils/Rectangle.h"
#include <iostream>

bool Rectangle::inside(float x, float y) const
{
    if (x >= topLeft.x && x <= bottomRight.x && y >= topLeft.y && y <= bottomRight.y) {
        return true;
    }

    return false;
}

bool Rectangle::intersects(const Rectangle& rect) const
{
    Vector2f leftBottom = Vector2f(rect.topLeft.x, rect.bottomRight.y);
    Vector2f rightTop = Vector2f(rect.bottomRight.x, rect.topLeft.y);

    if (inside(rect.topLeft) || inside(rect.bottomRight) || inside(leftBottom) || inside(rightTop)) {
        return true;
    }
    return false;
}

