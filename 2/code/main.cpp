#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <time.h>
using namespace std;


//class student, containing name and grade
//we can look up one student's name or grade
class Eleve
{	
	string nom;//student name
	int note;//student grade
public:
	//constructor
	Eleve(string NomEleve, int NoteEleve)
	{
		nom = NomEleve;//student name
		note = NoteEleve;//student grade
	}
	//deconstructor
	~Eleve(){}
	//get student name
	string Name(){ return nom; }
	//get student grade
	int Note(){ return note; }
};

//class to compare two students' names
//during the comparaison, we record the times
class CompareNom
{
public:
	//global pointer, public variable
	//record the times of comparison
	int *ptr;
	//redine an operator of ()
	//to execute a comparison
	int operator () (Eleve Stu1, Eleve Stu2)
	{
		//compare one time, counter add one
		(*ptr)++;
		//compare
		if (Stu1.Name() == Stu2.Name())
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
};

//class to compare two students' notes
//record the times of comparison
class CompareNote
{
public:
	//global pointer, public variable
	//record the times of comparison
	int *ptr;
	//redine an operator of ()
	//to execute a comparison
	int operator () (Eleve Stu1, Eleve Stu2)
	{
		//compare one time
		(*ptr)++;
		//sort in order of descent
		if (Stu1.Note() <= Stu2.Note())
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
};

//generate a random string
//the name begins with a capital letter
//followed by one to 10 lowercase letters randomly drawn
string StringRandom ()
{
	//random string
	string StrRand;
	//first letter is uppercase
	StrRand = char(rand() % 26 + 'A');
	//the other letters are lowercase
	for (int i = 0; i < (rand() % 10 + 1); i++)
	{
		StrRand += char(rand() % 26 + 'a');
	}
	return StrRand;
}

int main ()
{
	// Initialize random seed
	srand(static_cast<unsigned int>(time(NULL)));
	//vector for student
	vector <Eleve> Stu;
	//number of students
	const int numStu = 10;
	//array for student grades
	int Note[numStu];
	//array for student names
	string Nom[numStu];
	//initialise student names and grades
	for (int i = 0; i < numStu; i++)
	{
		Note[i] = rand() % 21;
		Nom[i] = StringRandom();
		//construct a student instance
		//put this student into the vector
		Stu.push_back(Eleve(Nom[i], Note[i]));
	}

	cout << "Informations initiales:" << endl;
	//visit all students, print their name and grade
	for (vector<Eleve>::iterator iter = Stu.begin(); iter != Stu.end(); iter++)
	{
		cout << "nom: " << iter->Name() << " et note: " << iter->Note() << endl;
	}

	//instance
	CompareNom ComNom;
	CompareNote ComNote;

	//counter for compare
	int compteur = 0;
	//link to pointer
	ComNom.ptr = &compteur;
	ComNote.ptr = &compteur;
	//built-in function sort
	sort(Stu.begin(), Stu.end(), ComNote);

	//output result of sorting
	cout << endl << "Classement en descend en fonction de notes, avec ";
	cout << *ComNote.ptr << " fois de comparaison: " << endl;

	//print sorted student vector
	for (vector<Eleve>::iterator iter = Stu.begin(); iter != Stu.end(); iter++)
	{
		cout << "nom: " << iter->Name() << " et note: " << iter->Note() << endl;
	}
	cout << endl;
	system("pause");
	return 0;
}