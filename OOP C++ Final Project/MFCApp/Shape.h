#pragma once
#include <afx.h>

class Shape : public CObject
{
public:
	Shape();
	Shape(int, int);

	virtual void Draw(CClientDC *dc) = 0;
	virtual ~Shape();

	void SetX(const int&);
	int GetX() const;

	void SetY(const int&);
	int GetY() const;

private:
	int x1, y1;
};