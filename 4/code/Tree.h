#pragma once

#include<vector>
#include<iostream>
#include<string>
#include<queue>
#include"IntTree.h"
using namespace std;

template <typename T> // declaration of template 
class Tree
{
    T data; // Node information
    std::vector<Tree*> sons; // Sequence of sons (empty if none)
public:
	//Create a node with given information
    Tree(T d);
	//Destruct a node and all its descendants
    ~Tree();
	//Return information of this node
    T getData();
	//Set information of this node
    void setData(T d);
	//Return the number of sons of this node
    int nbSons();
	//Return the son at position pos, if any (considering left-most son is at position 0)
    Tree* getSon(int pos);
	//Replace the exisiting son at position pos with newSon (left-most son at position 0)
    void setSon(int pos, Tree* newSon);
	//Add newSon as supplementary right-most son of this node
    void addAsLastSon(Tree* newSon);
	//Remove right-most son of this node
	void removeLastSon();
	//display all element in a line
	void display();
	//display all element in another way
	void display(std::string prefix, std::string indent);
	//insert extra son at position pos, if exists
	void insertSon(int pos, Tree<T>* son);
	//remove son at position pos, thus reducing bnSons
	void removeSon(int pos);
	//pre-order in DFS
	static void preOrder(Tree<T>*);
	//post-order in DFS
	static void postOrder(Tree<T>*);
	//level-order in BFS
	static void levelOrder(Tree<T>*);
	//get max depth of tree
	static int maxDepth(Tree<T>*);
	//get min depth of tree
	static int minDepth(Tree<T>*);
};

//Create a node with given information
template <typename T>
Tree<T>::Tree(T d)
{
	data = d;
}

//Destruct a node and all its descendants
template <typename T>
Tree<T>::~Tree()
{
	for (int i = 0; i < nbSons(); i++)
	{
		delete sons[i];
	}
}

//Return information of this node
template <typename T>
T Tree<T>::getData()
{
	return data;
}

//Set information of this node
template <typename T>
void Tree<T>::setData(T d)
{
	data = d;
}

//Return the number of sons of this node
template <typename T>
int Tree<T>::nbSons()
{
	return sons.size();
}

//Return the son at position pos, if any (considering left-most son is at position 0)
template <typename T>
Tree<T>* Tree<T>::getSon(int pos)
{
	if (pos >= nbSons())
	{
		throw out_of_range("Cannot find a son in this position");
	}
	return sons[pos];
}

//Replace the exisiting son at position pos with newSon (left-most son at position 0) 
template <typename T>
void Tree<T>::setSon(int pos, Tree<T>* newSon)
{
	if (pos >= nbSons())
	{
		throw out_of_range("This position passes the range of son");
	}
	sons[pos] = newSon;
}

//Add newSon as supplementary right-most son of this node
template <typename T>
void Tree<T>::addAsLastSon(Tree<T>* newSon)
{
	sons.push_back(newSon);
}

//Remove right-most son of this node
template <typename T>
void Tree<T>::removeLastSon()
{
	if (nbSons() == 0)
	{
		throw out_of_range("Cannot delete any son because it is null");
	}
	delete sons[nbSons()-1];//delete last son of the current node
	sons.pop_back();//delete the last element of vector
}

//display all element in a line
template <typename T>
void Tree<T>::display()
{	
	cout << getData() << '\t';//print current data
	for (int i = 0; i < nbSons(); i++)//travel each son the current node
	{
		sons[i]->display();//recursively print its sons
	}
}

//display all element in a line in another way
template <typename T>
void Tree<T>::display(string prefix, string indent)
{
	cout << prefix << indent << data << endl;//print current data
	indent = indent + "  ";//update indent
	for (int i = 0; i < nbSons(); i++)//travel each son the current node
	{
		sons[i]->display(prefix, indent);//recursively print its sons
	}
}

//insert extra son at position pos, if exists
template <typename T>
void Tree<T>::insertSon(int pos, Tree<T>* son)
{
	if (pos >= nbSons())//error: out of range
	{
		throw out_of_range("Caonnot insert because of out of range");
	}
	sons.insert(sons.begin() + pos, son);//insert a son at this position
}

//remove son at position pos, thus reducing bnSons
template <typename T>
void Tree<T>::removeSon(int pos)
{
	if (pos >= nbSons())//error: out of range
	{
		throw out_of_range("Caonnot delete because of out of range");
	}
	sons.erase(sons.begin() + pos);//clear a son at this position
}

//pre-order in DFS
template<typename T>
void Tree<T>::preOrder(Tree<T>*t)
{
	cout << t->data << '\t';//parent node at first
	//son nodes
	for (int i = 0;i < t->nbSons();i++)
	{
		preOrder(t->sons[i]);//recursively print
	}
}

//post-order in DFS
template<typename T>
void Tree<T>::postOrder(Tree<T>*t)
{
	//son nodes at first
	for (int i = 0;i < t->nbSons();i++)
	{
		postOrder(t->sons[i]);//recursively print
	}
	cout << t->data << '\t';//parent node at last
}

//level-order in BFS
template<typename T>
void Tree<T>::levelOrder(Tree<T>*t)
{
	//fornt means the current node, at the same time the first one in queue
	//last means the last node in current level
	//nextLast means the last node in next level
	Tree<T> *front, *last, *nextLast;
	front = last = nextLast = t;//initialise
	queue<Tree<T>*> queueTree;//construct a queue
	queueTree.push(t);//put root node into the queue
	while (!queueTree.empty())//queue is not empty
	{
		front = queueTree.front();//take the first node in queue as current node
		queueTree.pop();//delete the first in queue
		cout << front->data << '\t';
		for (int i = 0;i<front->nbSons();i++)//visit all son nodes
		{
			queueTree.push(front->sons[i]);//put all son nodes into the queue
			nextLast = front->sons[i];//point to the last node in next level
		}
		if (front == last)//at the end of current level
		{
			cout << endl;//change level
			last = nextLast;//point to the last one in next level
		}
	}
}

//get max depth of tree
//in a recursive way
template<typename T>
int Tree<T>::maxDepth(Tree<T>*t)
{
	if (t->nbSons() == 0)//one node without sons
	{
		return 1;
	}
	else//nodes with at least son
	{
		int dep = 1;//depth of son tree
		for (int i = 0; i < t->nbSons(); i++)//visit all son nodes
		{
			int tempsDep = maxDepth(t->sons[i]) + 1;//get the depth for each son tree
			if (dep < tempsDep)//get the max depth among all son trees
			{
				dep = tempsDep;
			}
		}
		return dep;//return depth
	}
}

//get min depth of tree
//in a non-recursive way
template<typename T>
int Tree<T>::minDepth(Tree<T>*t)
{
	//fornt means the current node, at the same time the first one in queue
	//last means the last node in current level
	//nextLast means the last node in next level
	Tree<T> *front, *last, *nextLast;
	int depth = 1;//initial depth
	front = last = nextLast = t;//initialise
	queue<Tree<T>*> queueTree;//construct a queue
	queueTree.push(t);//put root node into the queue
	while (!queueTree.empty())//queue is not empty
	{
		front = queueTree.front();//take the first node in queue as current node
		queueTree.pop();//delete the first in queue
		if (front->nbSons() == 0)
		{
			//the node without son is a leaf node
			//we need it
			return depth;
		}
		for (int i = 0;i < front->nbSons();i++)//visit all son nodes
		{
			queueTree.push(front->sons[i]);//put all son nodes into the queue
			nextLast = front->sons[i];//point to the last node in next level
		}
		if (front == last)//at the end of current level
		{
			depth++;//change level
			last = nextLast;//point to the last one in next level
		}
	}
	return depth;
}