#include "Polynomial.h"
#include "Monomial.h"
#include <iostream>
#include <stdlib.h>

#define LIMIT 301	
using namespace std;

void RemoveChar(char*, char, bool);
bool CheckZero(char *);
Monomial Convert_Str_To_Mon(char *);

Polynomial::Polynomial()
{
	this->head = nullptr;
}
Polynomial::Polynomial(const Polynomial &p)
{
	this->head = nullptr;
	*this = p;
}
Polynomial::~Polynomial()
{
	Delete_List();
}

void Polynomial::print() const
{
	if (this->head == nullptr)
		cout << "0";
	else
		if ((this->head->Get_Coefficient() == 0) && (this->head->Get_Next() == nullptr))
			cout << 0;
		else
		{
			Monomial *h = this->head;
			bool no_zero = true;

			while (h != nullptr)
			{
				if (h->Get_Coefficient() != 0)
					h->print();
				else
					no_zero = false;

				h = h->Get_Next();

				if ((h != nullptr) && (h->Get_Coefficient() > 0) && no_zero)
					cout << "+";
			}
		}
}

void Polynomial::add(const Monomial &n)
{
	if (this->head == nullptr)
		this->head = new Monomial(n);
	else
		Find_A_Place(n);
}

void Polynomial::Find_A_Place(const Monomial &n)
{
	//state = 0 -> list beginning
	//state = 1 -> list middle
	//state = 2 -> end list

	Monomial *curr, *prev = this->head;

	if (Insert_Monomial(n, this->head, 0))
		return;

	if ((curr = this->head->Get_Next()) != nullptr)
		while (curr != nullptr)
		{
			if (Insert_Monomial(n, curr, 1, prev))
				return;

			prev = curr;
			curr = curr->Get_Next();
		}

	Insert_Monomial(n, prev, 2);
}

bool Polynomial::Insert_Monomial(const Monomial &n, Monomial *ptr, int state, Monomial *prev)
{
	int deg_n = n.Get_Degree();
	float co_n = n.Get_Coefficient(), sum = 0;
	Monomial* item = nullptr;

	if (deg_n > ptr->Get_Degree())
	{
		item = new Monomial(n);
		item->Set_Next(ptr);

		if (state == 0)
			this->head = item;
		if (state == 1)
			prev->Set_Next(item);

		return true;
	}
	if (deg_n == ptr->Get_Degree())
	{
		if ((sum = ptr->Get_Coefficient() + co_n) == 0)
		{
			if (state == 0)
			{
				item = this->head;
				if (this->head->Get_Next() != nullptr)
					this->head = this->head->Get_Next();
				else
					this->head = nullptr;
				delete item;
			}
			if (state == 1)
			{
				item = ptr;
				prev->Set_Next(ptr->Get_Next());
				delete item;
			}
		}
		else
			ptr->Set_Coefficient(sum);

		return true;
	}

	if (state == 2)
	{
		item = new Monomial(n);
		ptr->Set_Next(item);
		return true;
	}
	return false;
}

void Polynomial::Delete_List()
{
	Monomial*temp = this->head, *dlt;

	while (temp != nullptr)
	{
		dlt = temp;
		temp = temp->Get_Next();
		delete dlt;
	}

	this->head = nullptr;
}

int Polynomial::Get_Len(const Polynomial &p) const
{
	int count = 0;
	Monomial*temp = p.head;

	while (temp!=nullptr)
	{
		count++;
		temp = temp->Get_Next();
	}

	return count;
}

istream & operator>>(istream &cin, Polynomial &p)
{
	if (p.head != nullptr)
		p.Delete_List();

	int i, n = 0, start = 0;
	char*str = new char[LIMIT];
	cin.getline(str, LIMIT);
	
	char*sub_str = new char[strlen(str)];

	if (str[0] == '-')
	{
		start = 1;
		sub_str[0] = str[0];
		n++;
	}

	for (i = start; str[i] != ','; i++)
	{
		if ((str[i] != '-') && (str[i] != '+'))
			sub_str[n++] = str[i];
		else
		{
			sub_str[n] = '\0';
			n = 0;
			if (CheckZero(sub_str))
				p.add(Convert_Str_To_Mon(sub_str));
			if (str[i] == '-')
				sub_str[n++] = '-';
		}
	}

	sub_str[n] = '\0';
	p.add(Convert_Str_To_Mon(sub_str));

	delete[] sub_str;
	delete[] str;
	return cin;
}

ostream & operator<<(ostream &cout, const Polynomial &p)
{
	p.print();
	return cout;
}

Polynomial & Polynomial::operator=(const Polynomial &p)
{
	Delete_List();

	Monomial* temp = p.head;

	while (temp != nullptr)
	{
		this->add(*temp);
		temp = temp->Get_Next();
	}

	return *this;
}

Polynomial Polynomial::operator+(const Monomial &m) const
{
	Polynomial res = Polynomial(*this);
	res.add(m);
	return res;
}

Polynomial Polynomial::operator-(const Monomial &m) const
{
	Monomial res = Monomial(m);
	-res;
	return *this + res;
}

Polynomial Polynomial::operator+(const Polynomial &p) const
{
	Polynomial res = Polynomial(p);
	Monomial *this_ptr = this->head;

	while (this_ptr != nullptr)
	{
		res.add(*this_ptr);
		this_ptr = this_ptr->Get_Next();
	}

	return res;
}

Polynomial Polynomial::operator-(const Polynomial &p) const
{
	Polynomial res = Polynomial(p);
	-res;
	res += *this;
	return res;
}

Polynomial & Polynomial::operator-()
{
	Monomial*tmp = this->head;

	while (tmp != nullptr)
	{
		-*tmp;
		tmp = tmp->Get_Next();
	}

	return *this;
}

Polynomial & Polynomial::operator+=(const Polynomial &p)
{
	*this = *this + p;
	return *this;
}

Polynomial & Polynomial::operator-=(const Polynomial &p)
{
	*this = *this - p;
	return *this;
}

Polynomial & Polynomial::operator+=(const Monomial &m)
{
	this->add(m);
	return *this;
}

Polynomial & Polynomial::operator-=(const Monomial &m)
{
	Monomial res = Monomial(m);
	-res;
	return *this += res;
}

float Polynomial::operator()(const float &f) const
{
	float sum = 0;
	Monomial*tmp = this->head;

	while (tmp != nullptr)
	{
		sum += (*tmp)(f);
		tmp = tmp->Get_Next();
	}

	return sum;
}

bool Polynomial::operator==(const Polynomial &p) const
{
	if (Get_Len(*this) != Get_Len(p))
		return false;

	Monomial*ptr1 = this->head, *ptr2 = p.head;

	while (ptr1 != nullptr)
	{
		if (*ptr1 != *ptr2)
			return false;

		ptr1 = ptr1->Get_Next();
		ptr2 = ptr2->Get_Next();
	}

	return true;
}

bool Polynomial::operator!=(const Polynomial &p) const
{
	return !(*this == p);
}

bool Polynomial::operator==(const Monomial &m) const
{
	if (Get_Len(*this) != 1)
		return false;
	return *this->head == m ? true : false;
}

bool Polynomial::operator!=(const Monomial &m) const
{
	return !(*this == m);
}

float & Polynomial::operator[](const int &d)
{
	Monomial *mon = Find_Mon_In_List(d);

	if (mon != nullptr)
		return mon->Get_Coefficient_Ref();

	Delete_Zero();
	*this += Monomial(0, d);
	mon = Find_Mon_In_List(d);

	return mon->Get_Coefficient_Ref();
}

const float Polynomial::operator[](const int &d) const
{
	Monomial *mon = Find_Mon_In_List(d);
	return mon == nullptr ? 0 : mon->Get_Coefficient();
}

Monomial * Polynomial::Find_Mon_In_List(const int &d) const 
{
	Monomial *tmp = this->head;

	while (tmp != nullptr)
	{
		if (tmp->Get_Degree() == d)
			return tmp;

		tmp = tmp->Get_Next();
	}

	return nullptr;
}

void Polynomial::Delete_Zero()
{
	Monomial *temp = this->head, *prev = nullptr;
	while (temp != nullptr && temp->Get_Coefficient() == 0)
	{
		this->head = temp->Get_Next();
		delete temp;
		temp = this->head;
	}

	while (temp != NULL)
	{
		while (temp != nullptr && temp->Get_Coefficient() != 0)
		{
			prev = temp;
			temp = temp->Get_Next();
		}

		if (temp == nullptr)
			return;

		prev->Set_Next(temp->Get_Next());

		delete temp;
		temp = prev->Get_Next();
	}
}