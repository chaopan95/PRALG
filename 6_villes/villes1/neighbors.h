#pragma once

#include <vector>
using std::vector;

#include "point2d.h"
#include "square.h"
#include "quadrant.h"
#include "../quadtree/quadtree.h"

#if __cplusplus < 201103L
#ifndef NULL
#define NULL 0
#endif
#ifndef nullptr
#define nullptr NULL
#endif
#endif

#ifndef INFINITY
#define INFINITY 0x7fffffff
#endif

//
// Add point p in the quadtree representing the points in square s
//
template <typename T>
void insert(QuadTree< Point2D<T> >* &qtree, Square s, Point2D<T> p)
{
	if (qtree == nullptr)//this is an empty quadtree
	{
		qtree = new QuadLeaf<Point2D<T>>(p);//new node with point p
	}
	else if (!qtree->isLeaf())//current node is not leaf
	{
		Quadrant QT(s, p);//get the quadrant for p
		insert(qtree->son(QT.dir), QT.ssq, p);//get son node, construct sub-square, insert this point
	}
	else//current node is leaf
	{
		if (p == qtree->value())//current node has the same coordinates with the point, ignore the point
		{
			Point2D<T> curP = qtree->value();//current node of quadtree
			curP.addInfo(p.info());//add other name of town
			delete qtree;
			qtree = new QuadLeaf<Point2D<T>>(curP);//rebuild a point with mulpti-names
			return;
		}
		else
		{
			Point2D<T> curP = qtree->value();//current node of quadtree
			Quadrant curQ(s, curP);//the quadrant in which the current point is located
			delete qtree;//remove current node
			qtree = new QuadNode <Point2D<T>>; //creat a new quadtree wthin s
			qtree->son(curQ.dir) = new QuadLeaf<Point2D<T>>(curP);//set the current point as a son of new quadtree
			insert(qtree, s, p);//insert this point
		}
	}
}

//
// Add in vector neighbors the points q in quadtree qtree representing
// points in square s at euclidean distance less than r from point p
//
// Set only the nearest point if nearest is true
//
// Return the number of nodes visited
//
template <typename T>
int search(vector< Point2D<T> > &neighbors, QuadTree< Point2D<T> >* qtree, Square s, Point2D<T> p, float& r, bool nearest)
{
	if (s.intersects_disk(p, r))//if intersected between a circle and a square
	{
		if (qtree == nullptr)//empty quadtree
		{
			return 1;//zero node
		}
		else if (qtree->isLeaf())//current node is leaf
		{
			Point2D<T> curP = qtree->value();//current point

			if (curP.dist2(p) <= r * r)//in the circle of p
			{
				if (neighbors.empty())//vector is null
				{
					neighbors.push_back(curP);//append the point
				}
				else
				{
					if (nearest)//just keep the nearest point
					{
						//if new point is more closer than current point, replace the current point with new one
						//and the new one is not p
						if (neighbors[0].dist(p) > curP.dist(p) && p.info() != curP.info())
						{
							neighbors.clear();
							neighbors.push_back(curP);
						}
						//update r according to currently nearest point
						r = neighbors[0].dist(p);
					}
					else//keep all points in the circle of p
					{
						neighbors.push_back(curP);
					}
				}
			}
			return 1;
		}
		else//current node is not leaf
		{
			int nb = 1;//number of nodes visited
			for (int i = 0; i < nQuadDir; i++)
			{
				nb += search(neighbors, qtree->son(i), s.subsquare(i), p, r, nearest);//recursively search all nodes in four quadrants
			}
			return nb;
		}
	}
	else
	{
		return 1;//on node visited
	}
}

//
// Add in vector neighbors the nearest point of p in the quadtree qtree
// representing the points in square s
//
// Return the number of nodes visited
//
template <typename T>
int search(vector< Point2D<T> > &neighbors, QuadTree< Point2D<T> >* qtree, Square s, Point2D<T> p)
{
	float r = float(INFINITY); //radius is INFINITY
	return search(neighbors, qtree, s, p, r, true);//set nearest true
}

