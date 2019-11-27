/*
 * A simple class to operate on quadrants
 */

#include "quadrant.h"
#include <iostream>
using namespace std;

Quadrant::Quadrant(Square s, Point_2D p)//determine which quadrant for point p
{
	float x_deviation = p.x() - (s.x + s.w / 2);//difference between x and the center of the squqre
	float y_deviation = p.y() - (s.y + s.w / 2);//difference between x and the center of the squqre
	if (x_deviation <= 0 && y_deviation >= 0)//North West
	{
		dir = 0;
		ssq = s.subsquare(dir);
	}
	else if (x_deviation > 0 && y_deviation >= 0)//North East
	{
		dir = 1;
		ssq = s.subsquare(dir);
	}
	else if (x_deviation > 0 && y_deviation < 0)//South East
	{
		dir = 2;
		ssq = s.subsquare(dir);
	}
	else if (x_deviation <= 0 && y_deviation < 0)//South West
	{
		dir = 3;
		ssq = s.subsquare(dir);
	}
}