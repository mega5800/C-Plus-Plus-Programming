#include "stdafx.h"
#include "Line.h"
#include "Shape.h"

Line::Line(Circle* x, Circle* y)
{
	this->c_one = x;
	this->c_two = y;
}

Line::Line(const Line &l)
{
	*this = l;
}

Line & Line::operator=(const Line &l)
{
	this->c_one = l.c_one;
	this->c_two = l.c_two;

	return *this;
}

Line::~Line()
{
}

void Line::Draw(CClientDC * dc)
{
	CPen pen_line;
	pen_line.CreatePen(PS_SOLID, 4, RGB(30, 144, 255));
	dc->SelectObject(&pen_line);

	dc->MoveTo(this->c_one->GetPoint());
	dc->LineTo(this->c_two->GetPoint());
}
