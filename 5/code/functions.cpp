#include"functions.h"
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

//get a min among three numbers
inline int min3(int a, int b, int c)
{
	return min(min(a, b), c);
}
//get a min among four number
inline int min4(int a, int b, int c, int d)
{
	return min(min3(a, b, c), d);
}

//Levenshtein Distance in a recursive way wothout memory
//according to the current recursive equation
int LD_R(string s1, string s2, int i, int j)
{
	if (min(i, j) == 0)
	{
		return max(i, j);
	}
	else
	{
		int a, b, c;
		a = LD_R(s1, s2, i - 1, j - 1);//top left
		b = LD_R(s1, s2, i - 1, j) + 1;//top
		c = LD_R(s1, s2, i, j - 1) + 1;//left
		if (s1[i - 1] != s2[j - 1])
		{
			a++;
		}
		return min3(a, b, c);
	}
}

//Levenshtein Distance in a recursive way with memory
int LD_RM(string s1, string s2, int i, int j, int **m)
{
	if (min(i, j) == 0)
	{
		return max(i, j);
	}
	else
	{
		int a, b, c;
		a = LD_RM(s1, s2, i - 1, j - 1, m);//top left
		b = LD_RM(s1, s2, i - 1, j, m) + 1;//top
		c = LD_RM(s1, s2, i, j - 1, m) + 1;//left
		if (s1[i - 1] != s2[j - 1])
		{
			a++;
		}
		m[i - 1][j - 1] = min3(a, b, c);
		return m[i - 1][j - 1];
	}
}

//Levenshtein Distance in an iterative way
int LD_Iter(string s1, string s2, int **m)
{
	int len1 = s1.length();//length of s1
	int len2 = s2.length();//length of s2

	//initialise the first column with 0
	for (int i = 1; i <= len1; i++)
	{
		m[i][0] = i;
	}
	//initialise the first line with 0
	for (int j = 1; j <= len2; j++)
	{
		m[0][j] = j;//
	}

	int a, b, c;//neighbor values
	for (int i = 1; i <= len1; i++)
	{
		for (int j = 1; j <= len2; j++)
		{
			a = m[i - 1][j - 1];//top left
			b = m[i - 1][j] + 1;//top
			c = m[i][j - 1] + 1;//left
			if (s1[i - 1] != s2[j - 1])
			{
				a++;
			}
			m[i][j] = min3(a, b, c);
		}
	}
	return m[len1][len2];
}

//print the change step in detail
void printStepL(string s1, string s2, int **m)
{
	int len1 = s1.length();//length of s1
	int len2 = s2.length();//length of s2

	cout << s1;
	int a, b, c;//neighbor values
	//get a min value among a, b, c
	int minV;
	while (len1 != 0 || len2 != 0)
	{
		a = m[len1 - 1][len2 - 1];//top left
		b = m[len1 - 1][len2] + 1;//top
		c = m[len1][len2 - 1] + 1;//left
		if (s1[len1 - 1] != s2[len2 - 1])
		{
			a++;
		}
		minV = min3(a, b, c);
		//delete(cost 1)
		if (b == minV)
		{
			//delete s1[len1 - 1]
			cout << " --(delete \'" << s1[len1 - 1] << "\')--> ";
			for (int i = len1 - 1; i<int(s1.size()) - 1; i++)
			{
				s1[i] = s1[i + 1];
			}
			s1.resize(int(s1.size() - 1));
			cout << s1;
			len1--;
		}
		//insert(cost 1)
		else if (c == minV)
		{
			//insert s2[len2 - 1] at position len1-1 of s1
			cout << " --(insert \'" << s2[len2 - 1] << "\')--> ";
			s1.resize(s1.size() + 1);
			for (int i = int(s1.size()) - 1; i > len1 - 1; i--)
			{
				s1[i] = s1[i - 1];
			}
			s1[len1] = s2[len2 - 1];
			cout << s1;
			len2--;
		}
		//replace(cost 1)
		else//a == minV
		{
			if (s1[len1 - 1] != s2[len2 - 1])
			{
				//replace s1[len1 - 1] with s2[len2 - 1]
				cout << " --(replace \'" << s1[len1 - 1] << "\' with \'" << s2[len2 - 1] << "\')--> ";
				s1[len1 - 1] = s2[len2 - 1];
				cout << s1;
			}
			len1--;
			len2--;
		}
	}
	cout << endl;
}

//Damerau-Levenshtein Distance in a recursive way
int DLD_R(string s1, string s2, int i, int j)
{
	if (min(i, j) == 0)
	{
		return max(i, j);
	}
	else if (i > 1 && j > 1 && s1[i - 1] == s2[j - 2] && s1[i - 2] == s2[j - 1])
	{
		int a, b, c, d;
		a = DLD_R(s1, s2, i - 1, j - 1);//top left
		b = DLD_R(s1, s2, i - 1, j) + 1;//top
		c = DLD_R(s1, s2, i, j - 1) + 1;//left
		d = DLD_R(s1, s2, i - 2, j - 2) + 1;//before top left
		if (s1[i - 1] != s2[j - 1])
		{
			a++;
		}
		return min4(a, b, c, d);
	}
	else
	{
		int a, b, c;
		a = DLD_R(s1, s2, i - 1, j - 1);
		b = DLD_R(s1, s2, i - 1, j) + 1;
		c = DLD_R(s1, s2, i, j - 1) + 1;
		if (s1[i - 1] != s2[j - 1])
		{
			a++;
		}
		return min3(a, b, c);
	}
}

//Damerau-Levenshtein Distance in a recursive way with memory
int DLD_RM(string s1, string s2, int i, int j, int **m)
{
	if (min(i, j) == 0)
	{
		return max(i, j);
	}
	else if (i > 1 && j > 1 && s1[i - 1] == s2[j - 2] && s1[i - 2] == s2[j - 1])
	{
		int a, b, c, d;
		a = DLD_R(s1, s2, i - 1, j - 1);//top left
		b = DLD_R(s1, s2, i - 1, j) + 1;//top
		c = DLD_R(s1, s2, i, j - 1) + 1;//left
		d = DLD_R(s1, s2, i - 2, j - 2) + 1;//before top left
		if (s1[i - 1] != s2[j - 1])
		{
			a++;
		}
		m[i - 1][j - 1] = min4(a, b, c, d);
		return m[i - 1][j - 1];
	}
	else
	{
		int a, b, c;
		a = DLD_R(s1, s2, i - 1, j - 1);//top left
		b = DLD_R(s1, s2, i - 1, j) + 1;//top
		c = DLD_R(s1, s2, i, j - 1) + 1;//left
		if (s1[i - 1] != s2[j - 1])
		{
			a++;
		}
		m[i - 1][j - 1] = min3(a, b, c);
		return m[i - 1][j - 1];
	}
}

//Damerau-Levenshtein Distance in an iterative way
int DLD_Iter(string s1, string s2, int **m)
{
	int len1 = s1.length();//length of s1
	int len2 = s2.length();//length of s2

	//initialise the first column with 0
	for (int i = 1; i <= len1; i++)
	{
		m[i][0] = i;
	}
	//initialise the first row with 0
	for (int j = 1; j <= len2; j++)
	{
		m[0][j] = j;
	}

	int a, b, c, d;//neighbor values
	for (int i = 1; i <= len1; i++)
	{
		for (int j = 1; j <= len2; j++)
		{
			if (i > 1 && j > 1 && s1[i - 1] == s2[j - 2] && s1[i - 2] == s2[j - 1])
			{
				a = m[i - 1][j - 1];//top left
				b = m[i - 1][j] + 1;//top
				c = m[i][j - 1] + 1;//left
				d = m[i - 2][j - 2] + 1;//before top left
				if (s1[i - 1] != s2[j - 1])
				{
					a++;
				}
				m[i][j] = min4(a, b, c, d);
			}
			else
			{
				a = m[i - 1][j - 1];//top left
				b = m[i - 1][j] + 1;//top
				c = m[i][j - 1] + 1;//left
				if (s1[i - 1] != s2[j - 1])
				{
					a++;
				}
				m[i][j] = min3(a, b, c);
			}
		}
	}
	return m[len1][len2];
}

//print the change step of Levenshtein distance in detail
void printStepD(string s1, string s2, int **m)
{
	int len1 = s1.length();//length of s1
	int len2 = s2.length();//length of s2

	cout << s1;
	int a, b, c, d;//neighbor values
	//get a min value among a, b, c, d
	int minV;
	while (len1 != 0 || len2 != 0)
	{
		if (len1 > 1 && len2 > 1 && s1[len1 - 1] == s2[len2 - 2] && s1[len1 - 2] == s2[len2 - 1])
		{
			a = m[len1 - 1][len2 - 1];//top left
			b = m[len1 - 1][len2] + 1;//top
			c = m[len1][len2 - 1] + 1;//left
			d = m[len1 - 2][len2 - 2] + 1;//before top left
			if (s1[len1 - 1] != s2[len2 - 1])
			{
				a++;
			}
			minV = min4(a, b, c, d);
			//delete(cost 1)
			if (b == minV)
			{
				//delete s1[len1 - 1]
				cout << " --(delete \'" << s1[len1 - 1] << "\')--> ";
				for (int i = len1 - 1; i<int(s1.size()) - 1; i++)
				{
					s1[i] = s1[i + 1];
				}
				s1.resize(int(s1.size() - 1));
				cout << s1;
				len1--;
			}
			//insert(cost 1)
			else if (c == minV)
			{
				//insert s2[len2 - 1]
				cout << " --(insert \'" << s2[len2 - 1] << "\')--> ";
				s1.resize(s1.size() + 1);
				for (int i = int(s1.size()) - 1; i > len1 - 1; i--)
				{
					s1[i] = s1[i - 1];
				}
				s1[len1] = s2[len2 - 1];
				cout << s1;
				len2--;
			}
			else if (d == minV)
			{
				//swap s1[len1 - 1] with s1[len2 - 2]
				cout << " --(swap \'" << s1[len1 - 1] << "\' and \'" << s1[len1 - 2] << "\')--> ";
				char temp = s1[len1 - 1];
				s1[len1 - 1] = s1[len1 - 2];
				s1[len1 - 2] = temp;
				cout << s1;
				len1--;
				len2--;
			}
			//replace(cost 1)
			else//a == minV
			{
				if (s1[len1 - 1] != s2[len2 - 1])
				{
					//replace s1[len1 - 1] with s2[len2 - 1]
					cout << " --(replace \'" << s1[len1 - 1] << "\' with \'" << s2[len2 - 1] << "\')--> ";
					s1[len1 - 1] = s2[len2 - 1];
					cout << s1;
				}
				len1--;
				len2--;
			}
		}
		else
		{
			a = m[len1 - 1][len2 - 1];//top left
			b = m[len1 - 1][len2] + 1;//top
			c = m[len1][len2 - 1] + 1;//left
			if (s1[len1 - 1] != s2[len2 - 1])
			{
				a++;
			}
			minV = min3(a, b, c);
			//delete(cost 1)
			if (b == minV)
			{
				//delete s1[len1 - 1]
				cout << " --(delete \'" << s1[len1 - 1] << "\')--> ";
				for (int i = len1 - 1; i<int(s1.size()) - 1; i++)
				{
					s1[i] = s1[i + 1];
				}
				s1.resize(int(s1.size() - 1));
				cout << s1;
				len1--;
			}
			//insert(cost 1)
			else if (c == minV)
			{
				//insert s2[len2 - 1]
				cout << " --(insert \'" << s2[len2 - 1] << "\')--> ";
				s1.resize(s1.size() + 1);
				for (int i = int(s1.size()) - 1; i > len1 - 1; i--)
				{
					s1[i] = s1[i - 1];
				}
				s1[len1] = s2[len2 - 1];
				cout << s1;
				len2--;
			}
			//replace(cost 1)
			else//a == minV
			{
				if (s1[len1 - 1] != s2[len2 - 1])
				{
					//replace s1[len1 - 1] with s2[len2 - 1]
					cout << " --(replace \'" << s1[len1 - 1] << "\' with \'" << s2[len2 - 1] << "\')--> ";
					s1[len1 - 1] = s2[len2 - 1];
					cout << s1;
				}
				len1--;
				len2--;
			}
		}
	}
	cout << endl;
}