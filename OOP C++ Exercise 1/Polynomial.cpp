#include "Polynomial.h"
#include "Monomial.h"
#include <iostream>

using namespace std;

Polynomial::Polynomial()
{
	this->head = nullptr;
}

Polynomial::~Polynomial()
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