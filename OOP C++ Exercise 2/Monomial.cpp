#include "Monomial.h"
#include <iostream>
#include <stdlib.h>
#include <math.h>

#define LIMIT 51
using namespace std;

int Monomial::Number_Of_Monomials = 0;

void RemoveChar(char *s, char To_Remove, bool Check_All_Str)
{
	char remove_temp = To_Remove;
	int count = 0, i, len = strlen(s);

	for (i = 0; i < len; i++)
	{
		if (s[i] != remove_temp)
			s[count++] = s[i];

		if (((s[i] > 48) && (s[i] <= 57)) && !Check_All_Str)
		{
			Check_All_Str = true;
			remove_temp = 0;
		}

		if (s[i] == '^')
		{
			remove_temp = To_Remove;
			Check_All_Str = false;
		}
	}

	s[count] = '\0';
}

bool CheckZero(char *s)
{
	bool num_flag = false;
	int i, len = strlen(s);

	//case: x
	if (s[0] == 'x')
		return true;

	//case: -x
	if ((s[0] == '-') && (s[1] == 'x'))
		return true;

	for (i = 0; (s[i] != 'x') && (i < len); i++)
		if ((s[i] > 48) && (s[i] <= 57))
			num_flag = true;

	return num_flag;
}

float Get_Coefficient_From_Str(char*s)
{
	//case: s is empty
	if (s[0] == '\0')
		return 0;

	//case: -x
	if ((s[0] == '-') && (s[1] == 'x'))
		return -1;

	//case: x OR num*x
	float res = strtof(s, 0);
	return res == 0 ? 1 : res;
}
int Get_Degree_From_Str(char*s)
{
	bool x_flag = false;
	int i = -1, d_index = -1;

	while (s[i++] != '\0')
	{
		if (s[i] == 'x')
			x_flag = true;

		if (s[i] == '^')
			d_index = i;
	}

	if (!x_flag)
		return 0;

	if (x_flag && (d_index == -1))
		return 1;

	d_index++;
	int res, count = 0, len = strlen(s);
	char* str_d = new char[len];

	for (i = d_index; s[i] != '\0'; i++)
		str_d[count++] = s[i];

	str_d[count] = '\0';
	res = atoi(str_d);
	delete[] str_d;
	return res;
}

Monomial Convert_Str_To_Mon(char * s)
{
	RemoveChar(s, ' ', true);
	RemoveChar(s, '0', false);

	float c = Get_Coefficient_From_Str(s);
	int d = Get_Degree_From_Str(s);

	return Monomial(c, d);
}

Monomial::Monomial(float c, int d)
{
	this->coefficient = c;
	this->degree = d > 0 ? d : 0;
	this->next = nullptr;
	Number_Of_Monomials++;
}

Monomial::Monomial(const Monomial &m)
{
	this->coefficient = m.Get_Coefficient();
	int d = m.degree;
	this->degree = d > 0 ? d : 0;
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

float Monomial::Get_Coefficient() const
{
	return this->coefficient;
}
float & Monomial::Get_Coefficient_Ref()
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

void Monomial::Set_Degree(const int d)
{
	this->degree = d > 0 ? d : 0;
}

Monomial* Monomial::Get_Next() const
{
	return this->next;
}

void Monomial::Set_Next(Monomial *n)
{
	this->next = n;
}

Monomial Monomial::operator+(const Monomial &m) const
{
	if (this->degree == m.degree)
		return Monomial(this->coefficient + m.coefficient, this->degree);
	return *this;
}

Monomial Monomial::operator-(const Monomial &m) const
{
	if (this->degree == m.degree)
		return Monomial(this->coefficient - m.coefficient, this->degree);
	return *this;
}

Monomial & Monomial::operator-()
{
	this->coefficient *= -1;
	return *this;
}

Monomial Monomial::operator*(const Monomial &m) const
{
	Monomial res;

	res.coefficient = this->coefficient*m.coefficient;
	res.degree = this->degree + m.degree;

	return res;
}

Monomial Monomial::operator*(const float &f) const
{
	return *this*Monomial(f);
}

Monomial & Monomial::operator+=(const Monomial &m)
{
	*this = *this + m;
	return *this;
}

Monomial & Monomial::operator-=(const Monomial &m)
{
	*this = *this - m;
	return *this;
}

Monomial & Monomial::operator*=(const Monomial &m)
{
	*this = *this * m;
	return *this;
}

Monomial & Monomial::operator*=(const float &f)
{
	*this = *this * Monomial(f);
	return *this;
}

bool Monomial::operator==(const Monomial &m) const
{
	if ((this->Get_Coefficient() == m.coefficient) && (this->Get_Degree() == m.degree))
		return true;
	return false;
}

bool Monomial::operator!=(const Monomial &m) const
{
	return !(*this == m);
}

bool Monomial::operator!=(const float &f) const
{
	return !(*this == Monomial(f));
}

float Monomial::operator()(const float &f) const
{
	float res = powf(f, (float)this->degree);
	res *= this->coefficient;

	return res;
}

Monomial & Monomial::operator=(const Monomial &m)
{
	this->coefficient = m.coefficient;
	this->degree = m.degree;

	return *this;
}

istream & operator>>(istream & cin, Monomial & m)
{
	char*str = new char[LIMIT];
	cin.getline(str, LIMIT);
	
	m = (CheckZero(str)) ? Convert_Str_To_Mon(str) : Monomial(0, 0);

	delete[] str;
	return cin;
}

ostream & operator<<(ostream &cout, const Monomial &m)
{
	m.print();
	return cout;
}