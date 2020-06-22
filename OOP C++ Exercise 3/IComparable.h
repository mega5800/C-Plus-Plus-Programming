#pragma once

#ifndef ICOMPARABLE_h
#define ICOMPARABLE_h

template <class T>
class IComparable
{
public:
	virtual bool operator==(const T&) const = 0;
	virtual bool operator!=(const T&) const = 0;

	virtual bool operator<(const T&) const = 0;
	virtual bool operator>(const T&) const = 0;

	virtual bool operator<=(const T&) const = 0;
	virtual bool operator>=(const T&) const = 0;
};

#endif