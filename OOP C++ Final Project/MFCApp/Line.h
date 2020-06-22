#pragma once
#include "Shape.h"
#include "Circle.h"

class Line : public Shape
{
public:

	Circle *c_one;
	Circle *c_two;

	Line(Circle*, Circle*);
	Line(const Line&);
	Line& operator=(const Line&);
	virtual ~Line();

	// Inherited via Shape
	virtual void Draw(CClientDC * dc) override;
};