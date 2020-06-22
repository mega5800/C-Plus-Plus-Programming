#pragma once

#ifndef INTERVAL_H
#define INTERVAL_H

#include <iostream>
using namespace std;

class Interval
{
public:
	Interval();
	~Interval();

	void Set_Start(const float s);
	void Set_End(const float e);
	void Set_Color(const int c);

	float Get_Start() const;
	float Get_End() const;
	int Get_Color() const;

	void Print() const;

private:
	float start;
	float end;
	int color;
};

#endif