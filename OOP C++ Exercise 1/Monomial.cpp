#include "Monomial.h"
#include <iostream>

using namespace std;

int Monomial::Number_Of_Monomials = 0;

Monomial::Monomial(float c, int d) : degree(d < 0 ? 0 : d)
{
	this->coefficient = c;
	this->next = nullptr;
	Number_Of_Monomials++;
}

Monomial::Monomial(const Monomial &m) : degree(m.Get_Degree())
{
	this->coefficient = m.Get_Coefficient();
	this->next = nullptr;
	Number_Of_Monomials++;
}

Monomial::~Monomial()
{
	Number_Of_Monomials--;
}

int Monomial::getNumberOfMonomials()
{
	return Number_Of_Monomials;
}

void Monomial::print() const
{
	if ((this->coefficient == 0) && (this->degree >= 0) && (this->next != nullptr))
		return;

	if (this->coefficient == 0)
		cout << "0";
	else
		if (this->degree == 0)
			cout << this->coefficient;
		else
		{
			if (this->degree == 1)
			{
				if (this->coefficient == 1)
					cout << "x";
				else
					if (this->coefficient == -1)
						cout << "-x";
					else
						cout << this->coefficient << "*x";
			}
			else
			{
				if (this->coefficient == 1)
					cout << "x^" << this->degree;
				else
					if (this->coefficient == -1)
						cout << "-x^" << this->degree;
					else
						cout << this->coefficient << "*x^" << this->degree;
			}
		}
}

bool Monomial::add(const Monomial &m)
{
	if (this->degree == m.degree)
	{
		this->coefficient += m.coefficient;
		return true;
	}

	return false;
}

float Monomial::Get_Coefficient() const
{
	return this->coefficient;
}
void Monomial::Set_Coefficient(const float f)
{
	this->coefficient = f;
}

int Monomial::Get_Degree() const
{
	return this->degree;
}

Monomial* Monomial::Get_Next()
{
	return this->next;
}

void Monomial::Set_Next(Monomial *n)
{
	this->next = n;
}