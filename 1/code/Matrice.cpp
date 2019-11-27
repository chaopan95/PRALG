#include "Matrice.h"
#include <iostream>
#include <cassert>
#include <stdlib.h>
using namespace std;

//initialise matrix (i, j) with 0
Matrice::Matrice(int i, int j)
{
	//(i, j) both i and j is bigger than 0
	assert(i > 0 && j > 0);
	row = i;
	column = j;
	//initialise
	//all elements are 0
	tableau = new float[row * column];
	compteur = new int;
	//counter is 1
	*compteur = 1;
	cout << "Constructeur par ligne " << row << " et colonne:" << column << endl;
}

//initialise matrix with another one
Matrice::Matrice(const Matrice & M1)
{
	tableau = M1.tableau;
	row = M1.row;
	column = M1.column;
	compteur = M1.compteur;
	(*compteur)++;
	cout << "Constructeur par copie par ligne " << row << " et colonne " << column << endl;
}

//deconstruct
Matrice::~Matrice()
{
	if (*compteur == 1)
	{
		delete compteur;
		delete []tableau;
		cout << "Destructeur detruit tout" << endl;
	}
	else
	{
		(*compteur)--;
		cout << "Decremente dans le destructeur" << endl;
	}
}

//define operator for reading value of (i, j)
float &Matrice::operator () (int m, int n) const
{
	//affirme (m, n) is not out of range
	assert(m >= 0 && m < row && n >= 0 && n < column);
	return tableau[m * column + n];
}

//sum between two matrix
Matrice Matrice::operator + (Matrice & M1)
{
	//affirm tow matrix have a same size
	assert(row == M1.row && column == M1.column);
	//construct a new matrix
	Matrice newMat(row, column);
	//sum for each element
	for (int m = 0; m < row; m++)//row
	{
		for (int n = 0; n < column; n++)//column
		{
			newMat(m, n) = tableau[m * column + n] + M1(m, n);
		}
	}
	return newMat;
}

//multiply
Matrice Matrice::operator * (Matrice & M1)
{
	//affirm tow matrix have a same size
	assert(column == M1.row);
	//construct a new matrix
	Matrice newMat(row, M1.column);
	//multiply for each element
	for (int m = 0; m < row; m++)//row
	{
		for (int n = 0; n < M1.column; n++)//column
		{
			float sum = 0.0;
			for (int k = 0; k < column; k++)
			{
				sum += (tableau[m * column + k] * M1.tableau[k * M1.column + n]);
			}
			newMat(m, n) = sum;
		}
	}
	return newMat;
}

//copy a matrix
Matrice & Matrice::operator = (Matrice & M1)
{
	//affirm tow matrix have a same size
	assert (row == M1.row && column == M1.column);
	for (int m = 0; m < row; m ++)//row
	{
		for (int n = 0; n < column; n ++)//column
		{
			this->tableau[m * column + n] = M1.tableau[m * column + n];
		}
	}
	return *this;
}

//output matrix
ostream & operator << (ostream & MatrixOutPut, const Matrice & M)
{
	for (int m = 0; m < M.nRow(); m++)//row
	{
		for (int n = 0; n < M.nColumn(); n++)//column
		{
			MatrixOutPut << M(m, n) << '\t';
		}
		MatrixOutPut << endl;
	}
	return MatrixOutPut;
}

//construct a random matrix
void RandMatrice (Matrice &M)
{
	for (int m = 0; m < M.nRow (); m++)//row
	{
		for(int n = 0; n < M.nColumn (); n++)
		{
			M(m, n) = rand() % 10;
		}
	}
}