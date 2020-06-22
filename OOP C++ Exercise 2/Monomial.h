#pragma once

#ifndef MONOMIAL_H
#define MONOMIAL_H

#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

class Monomial
{
public:
	Monomial(float = 1, int = 0);
	Monomial(const Monomial&);

	~Monomial();

	static int getNumberOfMonomials();
	void print() const;

	float Get_Coefficient() const;
	float &Get_Coefficient_Ref();
	void Set_Coefficient(const float);

	int Get_Degree() const;
	void Set_Degree(const int);

	Monomial* Get_Next() const;
	void Set_Next(Monomial*);

	friend istream &operator>>(istream&, Monomial&);
	friend ostream &operator<<(ostream&, const Monomial&);
	friend void RemoveChar(char*, char, bool);
	friend bool CheckZero(char *);
	friend Monomial Convert_Str_To_Mon(char *);
	friend float Get_Coefficient_From_Str(char*);
	friend int Get_Degree_From_Str(char*);

	Monomial &operator=(const Monomial&);
	Monomial operator+(const Monomial&) const;
	Monomial operator-(const Monomial&) const;
	Monomial &operator-();
	Monomial operator*(const Monomial&) const;
	Monomial operator*(const float&) const;

	Monomial &operator+=(const Monomial&);
	Monomial &operator-=(const Monomial&);
	Monomial &operator*=(const Monomial&);
	Monomial &operator*=(const float&);

	bool operator==(const Monomial&) const;
	bool operator!=(const Monomial&) const;
	bool operator!=(const float&) const;

	float operator()(const float&) const;

private:
	float coefficient;
	int degree;
	static int Number_Of_Monomials;
	Monomial* next;
};

#endif