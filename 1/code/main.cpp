#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Matrice.h"
using namespace std;

int main ()
{
	// Initialize random seed
	srand(static_cast<unsigned int>(time(NULL)));
	//construct M1
	Matrice M1(3, 4);
	//initiale randomly M1
	RandMatrice(M1);
	//get value (1, 2)
	int value = M1(1 - 1, 2 - 1);
	//construct M2
	Matrice M2(4, 5);
	//initiale randomly M2
	RandMatrice(M2);
	//copy M1 to M3
	Matrice M3 = M1;
	//copy (M1*M2) to M4
	Matrice M4 = (M1 * M2);
	cout << endl << "Results:" << endl;
	cout << "Random matrix M1:" << endl << M1 << endl;
	cout << "Value of M1[1, 2]:" << value << endl << endl;
	cout << "Random matrix M2:" << endl << M2 << endl;
	cout << "After M3 = M1, M3:" << endl << M3 << endl;
	cout << "After M4 = M1*M2, M4:" << endl << M4 << endl;

	system("pause");
	return 0;
}