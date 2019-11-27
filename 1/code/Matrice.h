#pragma once

#include <iostream>
using namespace std;

class Matrice
{
	//stock all elements of matrix
	//one dimension
	float *tableau;
	int row, column;
	int *compteur;//counter
	
public:
	//construct function
	Matrice(int row, int col);
	Matrice(const Matrice &);
	//deconstruct function
	~Matrice();
	//get number of lines
	int nRow () const{ return row; }
	//get number of columns
	int nColumn() const { return column; }
	//define operator for reading value of (i, j)
	float & operator () (int i, int j) const;
	//sum between two matrix
	Matrice operator + (Matrice & B);
	//multiply
	Matrice operator * (Matrice & B);
	//copy a matrix
	Matrice & operator = (Matrice & A);
	//output matrix
	friend ostream & operator << (ostream & MatrixOutPut, const Matrice & M);
};
//construct a random matrix
void RandMatrice (Matrice &M);
