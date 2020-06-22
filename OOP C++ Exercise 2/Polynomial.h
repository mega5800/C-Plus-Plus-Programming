#pragma once

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <stdlib.h>
#include "Monomial.h"

using namespace std;

class Polynomial
{
public:
	Polynomial();
	Polynomial(const Polynomial&);
	~Polynomial();

	void print() const;
	void add(const Monomial&);

	friend istream &operator>>(istream&, Polynomial&);
	friend ostream &operator<<(ostream&, const Polynomial&);
	friend void RemoveChar(char*, char, bool);
	friend bool CheckZero(char *);
	friend Monomial Convert_Str_To_Mon(char *);

	Polynomial &operator=(const Polynomial&);
	Polynomial operator+(const Monomial&) const;
	Polynomial operator-(const Monomial&) const;
	Polynomial operator+(const Polynomial&) const;
	Polynomial operator-(const Polynomial&) const;
	Polynomial &operator-();
	Polynomial &operator+=(const Polynomial&);
	Polynomial &operator-=(const Polynomial&);
	Polynomial &operator+=(const Monomial&);
	Polynomial &operator-=(const Monomial&);
	float operator()(const float&) const;

	bool operator==(const Polynomial&) const;
	bool operator!=(const Polynomial&) const;

	bool operator==(const Monomial&) const;
	bool operator!=(const Monomial&) const;
	
	float & operator[](const int&);
	const float operator[](const int&)const;

private:
	Monomial *head;

	void Find_A_Place(const Monomial&);
	bool Insert_Monomial(const Monomial&, Monomial*, int, Monomial* = nullptr);
	void Delete_List();
	int Get_Len(const Polynomial&) const;
	Monomial *Find_Mon_In_List(const int&) const;
	void Delete_Zero();
};

#endif