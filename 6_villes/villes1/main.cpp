#include<iostream>
#include<string>
#include<vector>
#include<time.h>
#include<algorithm>
using namespace std;

#ifndef srcPath
#define srcPath ".."
#endif
// The path and name of the town file
string townFile = srcPath "/villes1/villes.txt";

#include"neighbors.h"
#include"town.h"


/*
 * Example of use of "town.h" and "villes.txt":
 * - read file of metropolitan French towns with coordinates
 * - display reading time and number of towns read
 * - ask for town name
 * - lookup for town coordinates with this name and display them
 * - display distance between two random towns
 */
int main()
{
    /////
    ///// Read town file
    /////
    // Create an empty list of towns
    vector<Town> towns;
    // Prepare limits
    float xmin = std::numeric_limits<float>::max();
    float ymin = std::numeric_limits<float>::max();
    float xmax = std::numeric_limits<float>::min();
    float ymax = std::numeric_limits<float>::min();

    // Read file
	cout << "Reading town file: " << townFile << endl;
    clock_t t1 = clock();
    int numTowns = Town::read_file(townFile, towns, xmin, ymin, xmax, ymax);
    clock_t t2 = clock();

    // Say how many towns have been read
	if (numTowns < 0)
	{
		cout << "No town found" << endl;
		return 1;
    }
	cout << "File read in " << ((float)(t2 - t1) / CLOCKS_PER_SEC) << " s" << endl;
	cout << "Number of towns in file: " << numTowns << endl;
	cout << "Bounding box: (" << xmin << "," << ymin << ")-(" << xmax << "," << ymax << ")" << endl;

	float w = max(xmax - xmin, ymax - ymin);
	Square s(xmin, ymin, w);

	string cityName = "Ponts";//(380.027, 6853.24)
	float cityX, cityY;

    // Operate on quadtree
	t1 = clock();
	QuadTree< Point2D<string> > *Tree_town = new QuadNode< Point2D<string> >;
	for (int i = 0; i < numTowns; i++)
	{
		Point2D<string> p(towns[i].x(), towns[i].y(), towns[i].name());
		//cout << i << " " << p.x() << " " << p.y() << " " << p.info() << endl;
		insert(Tree_town, s, p);
		
		if (p.info() == cityName)//come across the wanted city
		{
			cityX = p.x();//record its coordinates
			cityY = p.y();//Ponts (380.027, 6853.24)
		}
	}

	t2 = clock();
	cout << endl;
	cout << "Number of subtree: " << Tree_town->nTrees() << endl;
	cout << "Number of leaves: " << Tree_town->nLeaves() << endl;
	cout << "Number of nodes: " << Tree_town->nNodes() << endl;
	cout << "Time for building quadtree: " << ((float)(t2 - t1) / CLOCKS_PER_SEC) << "s" << endl;
	
	Point2D <string> cityPoint(cityX, cityY, cityName);//build a point for the city
	cout << "The coordinate of " << cityName << " is: (" << cityX << ", " << cityY << ")" << endl;

	vector< Point2D< string > > neighbors;//Create an empty list of towns
	
	cout << endl;
	int numVistedNodes = search(neighbors, Tree_town, s, cityPoint);//number of visited nodes
	cout << "Number of visited nodes with quadtree is: " << numVistedNodes << endl;
	cout << "Closest town to \'" << cityName << "\' is: " << endl;
	
	//neighbors has one closest town
	vector<string> sibling = neighbors[0].infos();//get all towns with same coordinates
	//output closest town names and coordinates
	for (vector<string>::iterator iter = sibling.begin();iter != sibling.end();iter++)//search all
	{
		if (*iter != cityName)//remove the searched town
		{
			cout << *iter << endl;
		}
	}
	cout << "Coordinates are: (" << neighbors[0].x() << ", " << neighbors[0].y() << ")" << endl;

	numVistedNodes = 0;//Zeroisation
	//search linearly in all towns
	for (vector<Town>::iterator iter = towns.begin();iter != towns.end();iter++)
	{
		numVistedNodes++;
		if (iter->name() == cityName)//find the city
		{
			break;
		}
	}
	cout << "Number of visited nodes with linear vector is: " << numVistedNodes << endl;

	cout << endl;
	srand(clock());//random seed
	t1 = clock();
	numVistedNodes = 0;//Zeroisation
	int k;//random number
	int numCity = 100;//number for picking random cities
	for (int i = 0; i < numCity; i++)
	{
		k = rand() % numTowns;//index of city in vector
		Point2D<string> p(towns[k].x(), towns[k].y(), towns[k].name());//build a point
		numVistedNodes += search(neighbors, Tree_town, s, p);
	}
	t2 = clock();
	cout << "Mean time of searching certain city with quadtree is: " << ((float)(t2 - t1) / (numCity*CLOCKS_PER_SEC)) << "s" << endl;
	cout << "Mean visited nodes is: " << numVistedNodes / float(numCity) << endl;

	t1 = clock();
	numVistedNodes = 0;
	for (int i = 0;i < numCity;i++)
	{
		k = rand() % numTowns;
		cityName = towns[k].name();//get a random city
		
		for (vector<Town>::iterator iter = towns.begin();iter != towns.end();iter++)
		{
			//search linearly in all towns
			numVistedNodes++;
			if (iter->name() == cityName)
			{
				break;
			}
		}
	}
	t2 = clock();
	cout << "Mean time of searching certain city with linear vector is: " << ((float)(t2 - t1) / (numCity*CLOCKS_PER_SEC)) << "s" << endl;
	cout << "Mean visited nodes is: " << numVistedNodes / float(numCity) << endl;

	system("pause");
    return 0;
}