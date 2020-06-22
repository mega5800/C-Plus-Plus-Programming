#include "stdafx.h"
#include "Circle.h"
#include "Shape.h"

Circle::Circle()
{
}

Circle::Circle(int a, int b) : Shape(a, b)
{
}

Circle::Circle(const Circle &c)
{
	*this = c;
}

Circle & Circle::operator=(const Circle &c)
{
	this->SetX(c.GetX());
	this->SetY(c.GetY());
	return *this;
}

Circle::~Circle()
{
}

CPoint Circle::GetPoint()
{
	return CPoint(this->GetX(), this->GetY());
}

void Circle::Draw(CClientDC * dc)
{
	int x = this->GetX(), y = this->GetY();
	dc->Ellipse(x - 20, y - 20, x + 20, y + 20);
}

bool Circle::operator==(const CPoint &p)
{
	int xx = this->GetX(), yy = this->GetY();
	if ((xx - 20 <= p.x) && (p.x <= xx + 20))
		if ((yy - 20 <= p.y) && (p.y <= yy + 20))
			return true;
	return false;
}