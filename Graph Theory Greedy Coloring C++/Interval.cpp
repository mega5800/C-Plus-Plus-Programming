#include "Interval.h"
#include <iostream>
using namespace std;

Interval::Interval()
{
	this->start = 0;
	this->end = 0;
	this->color = 0;
}

Interval::~Interval()
{
}

void Interval::Set_Start(const float s)
{
	this->start = s;
}
void Interval::Set_End(const float e)
{
	this->end = e;
}
void Interval::Set_Color(const int c)
{
	this->color = c;
}

float Interval::Get_Start() const
{
	return this->start;
}
float Interval::Get_End() const
{
	return this->end;
}
int Interval::Get_Color() const
{
	return this->color;
}

void Interval::Print() const
{
	cout << "[" << this->start << "," << this->end << "]";
}