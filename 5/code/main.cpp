#include<iostream>
#include<vector>
#include<time.h>
#include<string>
#include<algorithm>
#include"functions.h"
using namespace std;

int main()
{
	string s1 = "ecoles";//first sctring ecoles
	string s2 = "eclose";//second string eclose

	int len1 = int(s1.length());//length of s1
	int len2 = int(s2.length());//length of s2

	clock_t t1, t2;//record time

	//print s1 and s2
	cout << "The 1st word: " << s1 << endl << "The 2nd word: " << s2 << endl;
	
	//creat a null array with a size of (len1+1)*(len2+1)
	int **m = new int *[len1 + 1];
	for (int i = 0; i <= len1; i++)
	{
		m[i] = new int[len2 + 1]();
	}

	//for Levenshtein Distance
	//recursive method and iterative method
	cout << endl;
	cout << "Levenshtein Distance:" << endl;
	t1 = clock();
	cout << "recursive method without memory: " << LD_R(s1, s2, len1, len2);// without memory
	t2 = clock();
	cout << " in " << ((float)(t2 - t1) / CLOCKS_PER_SEC) << "s" << endl;

	t1 = clock();
	cout << "recursive method with memory: " << LD_RM(s1, s2, len1, len2, m);//with memory
	t2 = clock();
	cout << " in " << ((float)(t2 - t1) / CLOCKS_PER_SEC) << "s" << endl;

	t1 = clock();
	cout << "iterative method: " << LD_Iter(s1, s2, m);
	t2 = clock();
	cout << " in " << (float)(t2 - t1) / CLOCKS_PER_SEC << "s" << endl;
	//print each step of modification with Levenshtein Distance from s1 to s2
	printStepL(s1, s2, m);

	//for Levenshtein Distance
	//recursive method and iterative method
	cout << endl;
	cout << "Damerau-Levenshtein Distance:" << endl;
	t1 = clock();
	cout << "recursive method without memory: " << DLD_R(s1, s2, len1, len2);// without memory
	t2 = clock();
	cout << " in " << ((float)(t2 - t1) / CLOCKS_PER_SEC) << "s" << endl;

	t1 = clock();
	cout << "recursive method with memory: " << DLD_RM(s1, s2, len1, len2, m);//with memory
	t2 = clock();
	cout << " in " << ((float)(t2 - t1) / CLOCKS_PER_SEC) << "s" << endl;

	t1 = clock();
	cout << "iterative method: " << DLD_Iter(s1, s2, m);
	t2 = clock();
	cout << " in " << (float)(t2 - t1) / CLOCKS_PER_SEC << "s" << endl;
	//print each step of modification with Damerau-Levenshtein Distance from s1 to s2
	printStepD(s1, s2, m);

	//release memory
	for (int i = 0; i <= len1; i++)
	{
		delete[]m[i];
	}
	delete[]m;

	system("pause");
	return 0;
}