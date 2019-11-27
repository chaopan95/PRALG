#include"IntTree.h"
#include"Tree.h"
#include<iostream>
#include<string>
using namespace std;

int main()
{
	IntTree *root = new IntTree(12);//build root
	root->addAsLastSon(new IntTree(8));//add 8 as first son of root 12
	root->getSon(0)->addAsLastSon(new IntTree(4));//add 4 as first son of node 8
	root->getSon(0)->addAsLastSon(new IntTree(9));//add 9 as second son of node 8
	root->addAsLastSon(new IntTree(23));//add 23 as second son of root 12
	root->getSon(1)->addAsLastSon(new IntTree(17));//add 17 as first son of node 23
	root->getSon(1)->getSon(0)->addAsLastSon(new IntTree(15));//add 15 as first son of node 17

	string prefix = "*";//prefix
	string indent = "  ";//indent

	cout << "Exercise 2.2:" << endl;
	//print tree
	root->display();
	cout << endl << endl << "Exercise 2.3:" << endl;
	//print tree with prefix
	root->display(prefix, indent);
	delete root;//release memory

	cout << endl << "Exercise 3.7: Catch the errors" << endl;
	IntTree *root_test = new IntTree(1);//build a new root
	cout << "test getSon()" << endl;
	try
	{
		root_test->getSon(1);//no son
	}
	catch(std::out_of_range)//catch error
	{
		cout << "Cannot find a son in this position" << endl;
	}

	cout << "test setSon()" << endl;
	try
	{
		root_test->setSon(10, root_test);
	}
	catch(std::out_of_range)
	{
		cout << "This position passes the range of son" << endl;
	}

	cout << "test removeLastSon()" << endl;
	try
	{
		root_test->removeLastSon();//no son
	}
	catch (std::out_of_range)
	{
		cout << "Cannot delete any son because it is null" << endl;
	}
	delete root_test;//release memomry

	
	cout << endl << "For Tree" << endl;
	Tree<double> *rootT = new Tree<double>(12.1);//build root
	rootT->addAsLastSon(new Tree<double>(8.1));//add 8.1 as first son of root 12.1
	rootT->getSon(0)->addAsLastSon(new Tree<double>(4.1));//add 4.1 as first son of node 8.1
	rootT->getSon(0)->addAsLastSon(new Tree<double>(9.1));//add 9.1 as second son of node 8.1
	rootT->addAsLastSon(new Tree<double>(23.1));//add 23.1 as second son of root 12.1
	rootT->getSon(1)->addAsLastSon(new Tree<double>(17.1));//add 17.1 as first son of node 23.1
	rootT->getSon(1)->getSon(0)->addAsLastSon(new Tree<double>(15.1));//add 15.1 as first son of node 17.1
	
	cout << "Exercise 4:" << endl;
	cout << "Display of tree:" << endl;
	//print tree
	rootT->display();
	cout << endl << endl << "Display with prefix: " << endl;
	//print tree with prefix
	rootT->display(prefix, indent);

	cout << endl << "Add a son (30.1) at the second position:" << endl;
	//add a son with function addSon
	rootT->insertSon(1, new Tree<double>(13.1));
	//print tree
	rootT->display(prefix, indent);
	cout << endl << "Delete the second son of the root" << endl;
	//delete a node with function removeSon
	rootT->removeSon(1);
	rootT->display(prefix, indent);

	cout << endl << "Catch the errors" << endl;
	Tree<double> *rootT_test = new Tree<double>(1.1);//build a new root
	cout << "test getSon()" << endl;
	try
	{
		rootT_test->getSon(1);//no son
	}
	catch (std::out_of_range)//catch error
	{
		cout << "Cannot find a son in this position" << endl;
	}

	cout << "test setSon()" << endl;
	try
	{
		rootT_test->setSon(10, rootT_test);
	}
	catch (std::out_of_range)
	{
		cout << "This position passes the range of son" << endl;
	}

	cout << "test removeLastSon()" << endl;
	try
	{
		rootT_test->removeLastSon();//no son
	}
	catch (std::out_of_range)
	{
		cout << "Cannot delete any son because it is null" << endl;
	}

	cout << "test insertSon()" << endl;
	try
	{
		rootT_test->insertSon(1, new Tree<double>(1.1));
	}
	catch (std::out_of_range)
	{
		cout << "Caonnot insert because of out of range" << endl;
	}

	cout << "test removeSon()" << endl;
	try
	{
		rootT_test->removeSon(1);
	}
	catch (std::out_of_range)
	{
		cout << "Caonnot delete because of out of range" << endl;
	}
	delete rootT_test;//release memomry
	
	cout << endl << "Exercise 5:";
	cout << endl << "Pre-order:" << endl;
	//print tree in DFS from top to bottom
	Tree<double>::preOrder(rootT);
	cout << endl << "Post-order:" << endl;
	//print tree in DFS from bottom to top
	Tree<double>::postOrder(rootT);
	cout << endl << "Level-order:" << endl;
	//print tree in BFS level by level from top to down
	Tree<double>::levelOrder(rootT);

	cout << endl << "Max depth:" << endl;
	//get a max depth of tree in a recursive way
	cout << Tree<double>::maxDepth(rootT);
	cout << endl << "Min depth" << endl;
	//get a miin depth of tree in a non-recursive way
	cout << Tree<double>::minDepth(rootT) << endl;

	delete rootT;//release memory
	
	system("pause");
	return 0;
}