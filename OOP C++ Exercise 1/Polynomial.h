#pragma once

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include "Monomial.h"

using namespace std;

class Polynomial
{
public:
	Polynomial();
	~Polynomial();

	void print() const;
	void add(const Monomial&);

private:
	Monomial *head;

	void Find_A_Place(const Monomial&);
	bool Insert_Monomial(const Monomial&, Monomial*, int, Monomial* = nullptr);
};

#endif