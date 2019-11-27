#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;


//Abstract function
class Fonction
{
	/*
	In this class, we have defined a general function,
	its major function is get one value, get an inverse
	and calculate a derivative
	*/
public:
	//consctructor
	Fonction() {}

	//deconsctructor
	//virtual avoids a collision between base and heritage
	virtual ~Fonction() {}

	//evaluate the Function at x
	virtual float operator()(float x)const = 0;

	//get derivate of Fonction
	virtual Fonction* derivee() const = 0;

	//return a copy Fonction
	virtual Fonction* clone() const = 0;

	//get inverse of Fonction
	float inverse(float y) const;
};


//Function polynome
class Polynome :public Fonction
{
	/*
	This class show a polynominal function, when a
	set of coefficients is given, we can get its 
	accurate expression
	*/
protected:
	//coefficient
	vector<float> coef;

public:
	//constructor by default
	Polynome() {}

	//constructor with coefficient
	Polynome(vector<float> c) { coef = c; }

	//deconstructor
	~Polynome() {}

	//get coefficient
	vector<float> getCoeff() { return coef; }

	//redifine operator()
	virtual float operator()(float x) const;

	//redefine derivee
	virtual Fonction *derivee() const;

	//redefine copy
	virtual Fonction *clone() const;
};


//Function affine
class Affine :public Polynome
{
public:
	//two coefficients for a linear Fonction
	//a*x+b
	Affine(float a, float b)
	{
		//insert a, b
		coef.push_back(a);
		coef.push_back(b);
	}

	~Affine() {}
};


//Fonction trigo
class Trigo : public Fonction
{
	/*
	This class shows a trigonometric function, mainly including
	sin, cos and tan
	*/
private:
	//name of trigo Fonction, sin, cos, tan
	string nom;

public:
	Trigo(string s) { nom = s; }
	~Trigo() {}

	//redifine operator
	float operator()(float x) const;

	//redefine derrivee
	virtual Fonction* derivee() const;

	//redefine copy
	virtual Fonction* clone() const;
};


class Derivee : public Fonction
{
	/*
	In this class, we can get an approximate derivative
	valule at some x
	*/
public:
	Fonction *integrale;
	Derivee() {}
	~Derivee() {}
	//evaluate the Function at x
	virtual float operator()(float x)const;

	//redefine derrivee
	virtual Fonction* derivee() const;

	//redefine copy
	virtual Fonction* clone() const;
};