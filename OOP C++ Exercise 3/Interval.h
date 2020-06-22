#pragma once

#ifndef INTERVAL_H
#define INTERVAL_H

#include "IComparable.h"
#include "IPrintable.h"
#include <iostream>

using namespace std;

enum Interval_States
{
	VALID,
	INVALID,
	EMPTY
};

template <class T>
class Interval : public IComparable<Interval<T>>, public IPrintable
{
public:
	Interval<T>()
	{
	}

	Interval<T>(T s, T e)
	{
		this->is_valid = Get_Error(s, e);

		if (this->is_valid == VALID)
		{
			this->start = s;
			this->end = e;
		}
		else
		{
			this->start = 0;
			this->end = 0;
		}
	}

	~Interval<T>()
	{
	}

	T getStart() const
	{
		return this->start;
	}
	T getEnd() const
	{
		return this->end;
	}
	Interval_States isValid() const
	{
		return this->is_valid;
	}

	void setStart(const T s)
	{
		this->start = s;
	}
	void setEnd(const T e)
	{
		this->end = e;
	}
	void getProblem() const
	{
		Interval_States a = this->is_valid;
		switch (a)
		{
		case INVALID:
			cout << "Invalid interval";
			break;
		case EMPTY:
			cout << "EMPTY";
			break;
		case VALID:
			cout << "(" << this->start << ", " << this->end << ")";
			break;
		}
	}

	bool contains(const int &num) const
	{
		if ((this->getStart() < num) && (num < this->getEnd()))
			return true;
		return false;
	}
	bool isBefore(const Interval<T> &i) const
	{
		return (*this < i);
	}
	bool isAfter(const Interval<T> &i) const
	{
		return (*this > i);
	}
	bool intersects(const Interval<T> &i) const
	{
		if ((this->getStart() < i.getStart()) && (i.getStart() < this->getEnd()) && (this->getEnd() < i.getEnd()))
			return true;
		else
			if ((i.getStart() < this->getStart()) && (this->getStart() < i.getEnd()) && (i.getEnd() < this->getEnd()))
				return true;
			else
				if ((this->getStart() < i.getStart()) && (i.getEnd() < this->getEnd()))
					return true;
				else
					if ((i.getStart() < this->getStart()) && (this->getEnd() < i.getEnd()))
						return true;
		return false;
	}


	friend ostream &operator<<(ostream& cout, const Interval<T>& i)
	{
		i.OUTPUT();
		return cout;
	}
	friend istream &operator>>(istream& cin, Interval<T>& i)
	{
		return cin;
	}
	friend Interval<T> operator&&(const Interval<T>&a, const Interval<T>&b)
	{
		return a.Get_Intersects(b);
	}
	friend Interval<T> operator||(const Interval<T>&a, const Interval<T>&b)
	{
		return a.Get_Unite(b);
	}

	// Inherited via IComparable
	virtual bool operator==(const Interval<T>& i) const override
	{
		if ((this->getStart() == i.getStart()) && (this->getEnd() == this->getEnd()))
			return true;
		return false;
	}
	virtual bool operator!=(const Interval<T>& i) const override
	{
		return !(*this == i);
	}
	virtual bool operator<(const Interval<T>& i) const override
	{
		if ((this->getStart() < i.getStart()) && (this->getEnd() < i.getEnd()))
			if (this->getEnd() <= i.getStart())
				return true;
		return false;
	}
	virtual bool operator>(const Interval<T>& i) const override
	{
		if ((this->getStart() > i.getStart()) && (this->getEnd() > i.getEnd()))
			if (this->getEnd() >= i.getStart())
				return true;
		return false;
	}
	virtual bool operator<=(const Interval<T>& i) const override
	{
		return ((*this < i) || (*this == i));
	}
	virtual bool operator>=(const Interval<T>& i) const override
	{
		return ((*this > i) || (*this == i));
	}

private:
	T start;
	T end;
	Interval_States is_valid;

	// Inherited via IPrintable
	virtual void INPUT() override
	{
	}
	virtual void OUTPUT() const override
	{
		getProblem();
	}
	Interval_States Get_Error(T s, T e)
	{
		if (s > e)
			return INVALID;
		if (s == e)
			return EMPTY;
		return VALID;
	}

	Interval<T> Get_Intersects(const Interval<T> &i) const
	{
		if ((this->getStart() < i.getStart()) && (i.getStart() < this->getEnd()) && (this->getEnd() < i.getEnd()))
			return Interval<T>(i.getStart(), this->getEnd());
		else
			if ((i.getStart() < this->getStart()) && (this->getStart() < i.getEnd()) && (i.getEnd() < this->getEnd()))
				return Interval<T>(this->getStart(), i.getEnd());
			else
				if ((this->getStart() < i.getStart()) && (i.getEnd() < this->getEnd()))
					return Interval<T>(i.getStart(), i.getEnd());
				else
					if ((i.getStart() < this->getStart()) && (this->getEnd() < i.getEnd()))
						return Interval<T>(this->getStart(), this->getEnd());

		return Interval<T>(0, 0);
	}
	Interval<T> Get_Unite(const Interval<T> &i) const
	{
		if ((this->getStart() < i.getStart()) && (i.getStart() < this->getEnd()) && (this->getEnd() < i.getEnd()))
			return Interval<T>(this->getStart(), i.getEnd());
		else
			if ((i.getStart() < this->getStart()) && (this->getStart() < i.getEnd()) && (i.getEnd() < this->getEnd()))
				return Interval<T>(i.getStart(), this->getEnd());
			else
				if ((this->getStart() < i.getStart()) && (i.getEnd() < this->getEnd()))
					return Interval<T>(this->getStart(), this->getEnd());
				else
					if ((i.getStart() < this->getStart()) && (this->getEnd() < i.getEnd()))
						return Interval<T>(i.getStart(), i.getEnd());

		return Interval<T>(2, 1);
	}
};

#endif