#pragma once
#include "Functions.h"
#include<vector>

//threshold
const float eps = float(pow(10, -5));

//get inverse of Fonction
float Fonction::inverse(float y) const
{
	int step = 100;//steps
	//initial values for x
	float x1 = float(1.0);
	float x2 = float(1.1);
	//iteration
	for (int i = 0; i < step; i++)
	{
		//reach the precision of answer
		if (fabs(x2 - x1) < eps) { break; }
		x1 = x2;
		//Newton method
		float derivative = (this->operator()(x1 + eps) - this->operator()(x1 - eps)) / (2 * eps);
		x2 = x1 + (y - this->operator()(x1)) / derivative;
	}
	return x2;
}


//redifine operator()
float Polynome::operator()(float x) const
{
	float fx = 0;//initialise an expression
	int np = int(coef.size());//number of polynomes
	for (int i = 0; i < np; i++)
	{
		fx += coef[i] * pow(x, np - 1 - i);//expression of polynom
	}
	return fx;
}

//redefine derivee
Fonction *Polynome::derivee() const
{
	int np = int(coef.size());//number of polynomes
	vector<float> coeff(np - 1);//coefficient for Derivative Fonction
	for (int i = 0; i < np - 1; i++)
	{
		coeff[i] = coef[i] * (np - 1 - i);//Derivative algorithm
	}
	return new Polynome(coeff);//return derivative polynome Fonction
}

//redefine copy
Fonction *Polynome::clone() const
{
	return new Polynome(*this);
}


//redifine operator
float Trigo::operator()(float x) const
{
	//cos(x)
	if (nom == "cos") { return cos(x); }
	//sin(x)
	else if (nom == "sin") { return sin(x); }
	//tan(x)
	else if (nom == "tan") { return tan(x); }
	//other names as error
	else { throw out_of_range("Error name"); }
}

//redefine derrivee
Fonction* Trigo::derivee() const
{
	//get a trigo Fonction according to name
	Derivee *D = new Derivee();
	//initialise integrale
	D->integrale = clone();
	return D;
}

//redefine copy
Fonction* Trigo::clone() const
{
	return new Trigo(*this);
}


//evaluate the Function at x
float Derivee::operator()(float x)const
{
	return (integrale->operator()(x + pow(10, -2)) - integrale->operator()(x - pow(10, -2))) / (2 * pow(10, -2));
}

//redefine derivee
Fonction* Derivee::derivee() const
{
	Derivee *D = new Derivee();
	D->integrale = clone();
	return D;
}

//redefine copy
Fonction* Derivee::clone() const
{
	return new Derivee(*this);
}