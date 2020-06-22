#pragma once
#include "Shape.h"

class Circle : public Shape
{
public:
	Circle();
	Circle(int, int);
	Circle(const Circle&);
	Circle& operator=(const Circle&);
	virtual ~Circle();

	int index;
	CPoint GetPoint();

	// Inherited via Shape
	virtual void Draw(CClientDC * dc) override;
	bool operator==(const CPoint&);
};