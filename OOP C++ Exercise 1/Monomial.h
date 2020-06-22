#pragma once

#ifndef MONOMIAL_H
#define MONOMIAL_H

using namespace std;

class Monomial
{
public:
	Monomial(float = 1, int = 0);
	Monomial(const Monomial&);
	~Monomial();

	static int getNumberOfMonomials();
	void print() const;

	bool add(const Monomial&);

	float Get_Coefficient() const;
	void Set_Coefficient(const float);

	int Get_Degree() const;

	Monomial* Get_Next();
	void Set_Next(Monomial*);

private:
	float coefficient;
	const int degree;
	static int Number_Of_Monomials;
	Monomial* next;
};

#endif