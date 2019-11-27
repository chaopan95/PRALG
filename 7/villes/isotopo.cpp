#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <set>
#include <map>
#include <algorithm>

#include "town.h"
#include "point2d.h"

using namespace std;

#ifndef srcPath
#define srcPath "."
#endif
// The path and name of the town file
const string townFile = srcPath "/villes.txt";

// Repetition histogram, 'mark' means name or coordiantes
template <typename T>
void repNameHist(map<T, int> M, string mark);

// Study French isotoponyms
int main() {
    // Read town file
    // Create an empty list of towns
    vector<Town> towns;
    // Read file
    cout << "Reading town file: " << townFile << endl;
    clock_t time1 = clock();
    int nb_towns = Town::read_file(townFile, towns);
    clock_t time2 = clock();
    // Sanity check
    if (nb_towns < 0) {
        cout << "Error while reading file" << endl;
        return 2;
    }
    if (nb_towns == 0) {
        cout << "No town found" << endl;
        return 1;
    }

    // Initialize random seed
    srand(static_cast<unsigned int>(time(nullptr)));
    // Say how many towns have been read
    cout << "File read in: "
         << ((time2-time1)/CLOCKS_PER_SEC) << " s" << endl;
    cout << "Number of towns in file: "
         << towns.size() /* same as nb_towns */ << endl;
    cout << "A random town, using format \"name[lat,lon](x,y)\": "
         << towns[unsigned(rand()) % towns.size()] << endl;

    cout << endl;
    map<string, int> mapName;//city name as a key, number of repetition as value
    map<string, int>::iterator iterName;//iterator for searching
    map<Point2D, int> mapCoor;//city coordinates as a keym number of repetition as value
    map<Point2D, int>::iterator iterPoint;//iterator for searching

    for (unsigned int i = 0; i < unsigned(nb_towns); i++)
    {
        iterName = mapName.find(towns[i].name());//try to find a city name
        iterPoint = mapCoor.find(towns[i].point());//try to find a pair of coordinates

        if (iterName == mapName.end())//fail to find this city name
        {
            mapName.insert(pair<string, int>(towns[i].name(), 1));//insert the city, this is the first time to appear
        }
        else
        {
            (iterName->second)++;//same name, repeat another time
        }
        if (iterPoint == mapCoor.end())//fail to find such coordinates
        {
            mapCoor.insert(pair<Point2D, int>(towns[i].point(), 1));//insert the city, this is the first time to appear
        }
        else
        {
            (iterPoint->second)++;//find it successfully, repeat another time
        }
    }

    cout << "Q1:" << endl;
    repNameHist(mapName, "name");//histogram for names
    cout << "Q2:" << endl;
    repNameHist(mapCoor, "coordinates");//histogram for coordinates

    //all N cities that have another city of the same name
    set<Town> N;
    //all C cities that have another city of the same coordiantes
    set<Town> C;

    //travel in map of Name
    for (map<string, int>::iterator iter = mapName.begin(); iter != mapName.end(); iter++)
    {
        if (iter->second >= 2)//at least two cities have a common name
        {
            //get a list of town according to a same name
            vector<Town> T = Town::towns_with_name(towns, iter->first);
            //put all these towns in set N
            for (unsigned int i = 0; i < T.size(); i++)
            {
                N.insert(T[i]);
            }
        }
    }
    cout << "Q3:" << endl;
    cout << "Number of cities with same names is: " << N.size() << endl;

    //travel in map of Coordiantes
    for (map<Point2D, int>::iterator iter = mapCoor.begin(); iter != mapCoor.end(); iter++)
    {
        if (iter->second >= 2)//at least two cities have a common coordiante
        {
            //get a list of town according to a same pair of coordiantes
            vector<Town> T = Town::towns_with_x_y(towns, iter->first.x(), iter->first.y());
            //put all these towns into set C
            for (unsigned int i = 0; i<T.size(); i++)
            {
                C.insert(T[i]);
            }
        }
    }
    cout << "Number of cities with same coordinates is: " << C.size() << endl;

    //construct an empty vector for stocking an intersection between N and C
    vector<Town> intsc(min(N.size(), C.size()));//size of intersect
    vector<Town>::iterator iter;//iterator for searching
    //call in-built function set_intersection
    iter = set_intersection(N.begin(), N.end(), C.begin(), C.end(), intsc.begin());
    intsc.resize(unsigned(iter - intsc.begin()));//adjust the size of vector
    cout << "Number of all intersections is: " << intsc.size() << endl;

    cout << endl;
    //construct an empty vector for stocking mistaked towns
    set<Town> mistake;
    time1 = clock();
    for (unsigned int t1 = 0; t1 < intsc.size(); t1++)//town 1
    {
        for (unsigned int t2 = 0; t2 < intsc.size(); t2++)//town 2
        {
            //coord(t1)=coord(t2), but name(t1)!=name(t2)
            if (intsc[t1].x() == intsc[t2].x() && intsc[t1].y() == intsc[t2].y() && intsc[t1].name() != intsc[t2].name())
            {
                for (unsigned int t3 = 0; t3 < intsc.size(); t3++)//town 3
                {
                    //name(t1)=name(t3), but coord(t1)!=coord(t3)
                    if (intsc[t1].name() == intsc[t3].name() && (intsc[t1].x() != intsc[t3].x() || intsc[t1].y() != intsc[t3].y()))
                    {
                        for (unsigned int t4 = 0; t4 < intsc.size(); t4++)//town 4
                        {
                            //coord(t3)=coord(t4), but name(t3)!=name(t4)
                            if (intsc[t3].x() == intsc[t4].x() && intsc[t3].y() == intsc[t4].y() && intsc[t3].name() != intsc[t4].name())
                            {
                                //name(t2)=name(t4), but coord(t2)!=coord(t4)
                                if (intsc[t2].name() == intsc[t4].name() && (intsc[t2].x() != intsc[t4].x() || intsc[t2].y() != intsc[t4].y()))
                                {
                                    //append mistaked towns into set
                                    mistake.insert(intsc[t1]);
                                    mistake.insert(intsc[t2]);
                                    mistake.insert(intsc[t3]);
                                    mistake.insert(intsc[t4]);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    time2 = clock();
    cout << "Q4:" << endl;
    cout << "Number of mistaked towns is: " << mistake.size() << endl;
    if (mistake.size())
    {
        cout << "Time for finding mistaked towns is: " << ((time2 - time1) / CLOCKS_PER_SEC) << "s" << endl;
        cout << "Mistaked towns are: " << endl;
        for (set<Town>::iterator iter = mistake.begin(); iter != mistake.end(); iter++)
        {
            cout << iter->name() << endl;
        }
    }

    // That's all folks
    return 0;
}

// Repetition histogram, 'mark' means name or coordiantes
template <typename T>
void repNameHist(map<T, int> M, string mark)
{
    // Histogram for counting the number of numbers of repetitions
    map<int, int> hist;
    // Iterator for searching
    map<int, int>::iterator iterHist;
    for (typename map<T, int>::iterator iter = M.begin(); iter != M.end(); iter++)
    {
        // Try to find appearing times
        iterHist = hist.find(iter->second);
        if (iterHist == hist.end())
        {
            // Fail to find appearing times, insert it as a first
            hist.insert(pair<int, int>(iter->second, 1));
        }
        else
        {
            // Number of appearing times add 1
            (iterHist->second)++;
        }
    }

    // Output all numbers of appearing times
    for (map<int, int>::iterator iter = hist.begin(); iter != hist.end(); iter++)
    {
        cout << "Number of " << mark << " appearing " <<
                iter->first << " time(s) = " << iter->second << endl;
    }
    cout << endl;
}
