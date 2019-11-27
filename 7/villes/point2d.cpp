#include "point2d.h"

//
// Display 2D point
//
ostream &operator<<(ostream &os, Point2D const &pt) {
    return os << "(" << pt.x() << "," << pt.y() << ")";
}
ostream &operator<<(ostream &os, Point2D* const &p) {
    return os << *p;
}

// Define an operator < between two points
bool Point2D::operator < (const Point2D &pt) const
{
    // Compare x, if x of two points are identic, compare y
    return (_x < pt.x() || (_x == pt.x() && _y < pt.y()));
}
