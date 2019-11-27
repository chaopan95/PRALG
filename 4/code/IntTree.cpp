#include "IntTree.h"
#include<iostream>
#include<string>
#include<vector>
using namespace std;

//Create a node with given information
IntTree::IntTree(int d)
{
	data = d;
}

//Destruct a node and all its descendants
IntTree::~IntTree()
{
	for (int i = 0; i < nbSons(); i++)
	{
		delete sons[i];
	}
}

//Return information of this node
int IntTree::getData()
{
	return data;
}

//Set information of this node
void IntTree::setData(int d)
{
	data = d;
}

//Return the number of sons of this node
int IntTree::nbSons()
{
	return sons.size();
}

//Return the son at position pos, if any (considering left-most son is at position 0)
IntTree* IntTree::getSon(int pos)
{
	if (pos >= nbSons())
	{
		throw out_of_range("Cannot find a son in this position");
	}
	return sons[pos];
}

//Replace the exisiting son at position pos with newSon (left-most son at position 0)
void IntTree::setSon(int pos, IntTree* newSon)
{
	if (pos >= nbSons())
	{
		throw out_of_range("This position is out of the range of son");
	}
	sons[pos] = newSon;
}

//Add newSon as supplementary right-most son of this node
void IntTree::addAsLastSon(IntTree* newSon)
{
	sons.push_back(newSon);//append at last
}

//Remove right-most son of this node
void IntTree::removeLastSon()
{
	if (nbSons() == 0)
	{
		throw out_of_range("Cannot delete any son because it is null");
	}
	delete sons[nbSons()-1];//delete last son of the current node
	sons.pop_back();//delete the last element of vector
}

//display all element in a line
void IntTree::display()
{	
	cout << getData() << '\t';//print current data
	for (int i = 0; i < nbSons(); i++)//travel each son the current node
	{
		sons[i]->display();//recursively print its sons
	}
}

//display all element in a line in another way
void IntTree::display(string prefix, string indent)
{
	cout << prefix << indent << data << endl;//print current data
	indent = indent + "  ";//update indent
	for (int i = 0; i < nbSons(); i++)//travel each son the current node
	{
		sons[i]->display(prefix, indent);//recursively print its sons
	}
}