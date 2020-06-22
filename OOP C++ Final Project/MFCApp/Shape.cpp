#include "stdafx.h"
#include "Shape.h"

Shape::Shape()
{
}

Shape::Shape(int xx1, int yy1)
{
	this->x1 = xx1;
	this->y1 = yy1;
}

Shape::~Shape()
{
}

void Shape::SetX(const int &x)
{
	this->x1 = x;
}

int Shape::GetX() const
{
	return this->x1;
}

void Shape::SetY(const int &y)
{
	this->y1 = y;
}

int Shape::GetY() const
{
	return this->y1;
}
