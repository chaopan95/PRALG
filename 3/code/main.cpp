#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "Functions.h"
using namespace std;


//PI
const float PI = float(3.14159265359);

int main() 
{
	//coefficients for polynome, in order of descent
	//x^3+0*x^2+0*x^1+0*x^0, namely f(x) = x^3
	float p[] = { 1, 0, 0, 0 };
	//put the cefficients into a vector
	vector<float> f(p, p + 4);
	//construct a polynome Fonction f(x)=x^3
	Polynome fx(f);
	//compute x^3=27
	cout << "27^(1/3)=" << fx.inverse(27) << endl << endl;
	
	//construct a tan Function
	Trigo TAN("tan");
	//compute pi = 4*tan(1)
	cout << "4*atan(1)=" << (4 * TAN.inverse(1)) << endl;
	cout << "tan(PI/4)= " << TAN.operator ()(PI / 4) << endl;
	//compute tan'(PI/4), tan''(PI/4), tan'''(PI/4), tan''''(PI/4)
	cout << "tan'(PI/4)=" << TAN.derivee()->operator()(PI / 4) << endl;
	cout << "tan''(PI/4)=" << TAN.derivee()->derivee()->operator()(PI / 4) << endl;
	cout << "tan'''(PI/4)=" << TAN.derivee()->derivee()->derivee()->operator()(PI / 4) << endl;
	cout << "tan''''(PI/4)=" << TAN.derivee()->derivee()->derivee()->derivee()->operator()(PI / 4) << endl;

	//construct a linear Function
	//2*x+1
	Affine LinFun(2, 1);
	//empty vector for stocking the coefficients of linear Fonction
	vector<float> coef;
	//get coefficients
	coef = LinFun.getCoeff();
	cout << endl << "linear Function: f(x)=" << coef[0] << "x+" << coef[1] << endl;
	//solve 2*x+1=4
	cout << "Solve f(x)=" << coef[0] << "x+" << coef[1] << "=4:" << endl;
	cout << "x=" << LinFun.inverse(4) << endl;

	system("pause");
	return 0;
}