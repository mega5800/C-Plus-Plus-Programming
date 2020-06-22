#include "Date.h"
#include "IComparable.h"
#include "IPrintable.h"
#include <iostream>

using namespace std;
#define LIMIT 50

Date::Date()
{
}

Date::Date(int d, int m, int y)
{
	this->day = d;
	this->month = m;
	this->year = y;
	Check_Date();
}

Date::~Date()
{
}

void Date::setDay(const int d)
{
	this->day = d;
	Check_Date();
}

void Date::setMonth(const int m)
{
	this->month = m;
	Check_Date();
}

void Date::setYear(const int y)
{
	this->year = y;
	Check_Date();
}

int Date::getDay() const
{
	return this->day;
}

int Date::getMonth() const
{
	return this->month;
}

int Date::getYear() const
{
	return this->year;
}

Date & Date::operator=(const Date &d)
{
	this->day = d.day;
	this->month = d.month;
	this->year = d.year;
	Check_Date();
	return *this;
}

Date_States Date::isValid() const
{
	return this->is_valid;
}

void Date::getProblem() const
{
	Date_States a = this->is_valid;
	switch (a)
	{
	case INVALID_DAY:
		cout << "Illegal day for month";
		break;
	case INVALID_MONTH:
		cout << "Illegal month";
		break;
	case NOT_LEAP_YEAR:
		cout << "Not a leap year";
		break;
	case DATE_VALID:
		Print_Num(this->day, true);
		Print_Num(this->month, true);
		Print_Num(this->year, false, false);
		break;
	}
}

bool Date::operator==(const Date &d) const
{
	if (this->getDay() != d.day)
		return false;
	if (this->getMonth() != d.month)
		return false;
	if (this->getYear() != d.year)
		return false;
	return true;
}

bool Date::operator!=(const Date &d) const
{
	return !(*this == d);
}

bool Date::operator<(const Date &d) const
{
	if (this->getYear() < d.getYear())
		return true;
	else
		if (this->getYear() > d.getYear())
			return false;

	if (this->getMonth() < d.getMonth())
		return true;
	else
		if (this->getMonth() > d.getMonth())
			return false;

	if (this->getDay() < d.getDay())
		return true;
	else
		if (this->getDay() > d.getDay())
			return false;

	return false;
}

bool Date::operator>(const Date &d) const
{
	if ((*this != d) && !(*this < d))
		return true;
	return false;
}

bool Date::operator<=(const Date &d) const
{
	return (*this == d) || (*this < d);
}

bool Date::operator>=(const Date &d) const
{
	return (*this == d) || (*this > d);
}

void Date::INPUT()
{
	int a[3] = { 0 };
	int shift, len, i, n;

	char str[LIMIT];
	cin.getline(str, LIMIT);

	RemoveChar(str, ' ', true);
	RemoveChar(str, '0', false);

	len = My_Str_Len(str);

	for (i = 0; i < 3; i++)
	{
		a[i] = atoi(str);
		if (i < 2)
		{
			shift = Find_Slash(str) + 1;
			for (n = 0; n < len; n++)
				str[n] = str[n + shift];
			str[n] = '\0';
		}
	}
	this->day = a[0];
	this->month = a[1];
	this->year = a[2];
	Check_Date();
}

void Date::OUTPUT() const
{
	getProblem();
}

void Date::Print_Num(int num, bool flag, bool is_not_year) const
{
	if ((num < 10) && (is_not_year))
		cout << "0" << num;
	else
		cout << num;

	if (flag)
		cout << "/";
}

int Date::My_Str_Len(const char *str) const
{
	int count = 0;
	while (str[count] != '\0')
		count++;

	return count;
}

void Date::RemoveChar(char *s, char To_Remove, bool Check_All_Str) const
{
	char remove_temp = To_Remove;
	int count = 0, i, len = My_Str_Len(s);

	for (i = 0; i < len; i++)
	{
		if (s[i] != remove_temp)
			s[count++] = s[i];

		if (((s[i] > 48) && (s[i] <= 57)) && !Check_All_Str)
		{
			Check_All_Str = true;
			remove_temp = 0;
		}

		if (s[i] == '/')
		{
			remove_temp = To_Remove;
			Check_All_Str = false;
		}
	}

	s[count] = '\0';
}

int Date::Find_Slash(char *s) const
{
	int count = 0;
	while ((s[count] != '/') && (s[count] != '\0'))
		count++;

	return count;
}

void Date::Check_Date()
{
	int d = this->day, m = this->month;
	int valid[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

	if ((m < 0) || (m > 12))
	{
		this->is_valid = INVALID_MONTH;
		return;
	}

	if ((day == 29) && (month == 2))
	{
		if (!Leap_Year_Check(year))
			this->is_valid = NOT_LEAP_YEAR;
		else
			this->is_valid = DATE_VALID;
		return;
	}

	if ((d < 0) || (day > valid[month - 1]))
	{
		this->is_valid = INVALID_DAY;
		return;
	}

	this->is_valid = DATE_VALID;
}

bool Date::Leap_Year_Check(int year) const
{
	if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
		return true;
	return false;
}

ostream & operator<<(ostream &cout, const Date &d)
{
	d.OUTPUT();
	return cout;
}

istream & operator>>(istream &cin, Date &d)
{
	d.INPUT();
	return cin;
}