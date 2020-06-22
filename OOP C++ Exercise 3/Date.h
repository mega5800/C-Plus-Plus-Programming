#pragma once

#ifndef DATE_H
#define DATE_H

#include "IComparable.h"
#include "IPrintable.h"
#include <iostream>

using namespace std;
#define LIMIT 50

enum Date_States
{
	DATE_VALID,
	NOT_LEAP_YEAR,
	INVALID_DAY,
	INVALID_MONTH
};

class Date : public IComparable<Date>, public IPrintable
{
public:
	Date();
	Date(int, int, int);
	~Date();

	void setDay(const int);
	void setMonth(const int);
	void setYear(const int);

	int getDay() const;
	int getMonth() const;
	int getYear() const;

	friend ostream &operator<<(ostream&, const Date&);
	friend istream &operator>>(istream&, Date&);
	Date &operator=(const Date&);

	Date_States isValid() const;
	void getProblem()const;

	// Inherited via IComparable
	virtual bool operator==(const Date &) const override;
	virtual bool operator!=(const Date &) const override;
	virtual bool operator<(const Date &) const override;
	virtual bool operator>(const Date &) const override;
	virtual bool operator<=(const Date &) const override;
	virtual bool operator>=(const Date &) const override;

private:
	int day;
	int month;
	int year;
	Date_States is_valid;

	bool Leap_Year_Check(int) const;
	void Print_Num(int, bool, bool = true) const;
	int My_Str_Len(const char*) const;
	int Find_Slash(char*) const;
	void Check_Date();
	void RemoveChar(char*, char, bool) const;

	// Inherited via IPrintable
	virtual void INPUT() override;
	virtual void OUTPUT() const override;
};

#endif