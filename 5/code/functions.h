#pragma once

#include<string>
using namespace std;

//get a min among three numbers
inline int min3(int, int, int);

//get a min among four number
inline int min4(int, int, int, int);

//Levenshtein Distance in a recursive way wothout memory
//according to the current recursive equation
int LD_R(string, string, int, int);

//Levenshtein Distance in a recursive way with memory
int LD_RM(string, string, int, int, int **);

//Levenshtein Distance in an iterative way
int LD_Iter(string, string, int **);

//print the change step of Levenshtein distance in detail
void printStepL(string, string, int **);

//Damerau-Levenshtein Distance in a recursive way
int DLD_R(string, string, int, int);

//Damerau-Levenshtein Distance in a recursive way with memory
int DLD_RM(string, string, int, int, int **);

//Damerau-Levenshtein Distance in an iterative way
int DLD_Iter(string, string, int **);

//print the change step of Levenshtein distance in detail
void printStepD(string, string, int **);