/*
 * A simple class to operate on quadrants
 */

#include "point2d.h"
#include "../quadtree/quadtree.h"
#include "square.h"

Square Square::subsquare(int dir)
{
	float nX, nY; //new X, new Y
	if (!(dir == 0 || dir == 1 || dir == 2 || dir == 3))// dir must be 0,1,2,3
	{
		throw new std::out_of_range("Direction is wrong");
	}
	else
	{
		switch (dir)
		{
		case 0:// North-West
			nX = x;
			nY = y + w / 2;
			break;
		case 1:// North-East
			nX = x + w / 2;
			nY = y + w / 2;
			break;
		case 2:// South-East
			nX = x + w / 2;
			nY = y;
			break;
		case 3:// South-West
			nX = x;
			nY = y;
			break;
		default://exception
			throw new std::out_of_range("Not a case of 2D");
			break;
		}
	}
	Square nSubsqure(nX, nY, w / 2);//new sub square
	return nSubsqure;
}

bool Square::intersects_disk(Point_2D p, float r)
{
	Point_2D center(x + w / 2, y + w / 2);//locate the center of the square
	float distance2 = center.dist(p);//distance between the center and p
	if (distance2 <= r + w / 2)//the circle intersects with the square surely
	{
		return true;
	}
	else if (distance2 > r + w * sqrt(2) / 2)//the square doesn't intersect with the square surely
	{
		return false;
	}
	//if horizontal distance or vertical distance is smaller r, the square intersects with the circle
	else if (fabs(p.x() - x) <= r || fabs(p.x() - (x + w)) <= r || fabs(p.y() - y) <= r || fabs(p.y() - (y + w)) <= r)
	{
		return true;
	}
	else
	{
		return false;
	}
}