#pragma once

#ifndef IPRINTABLE_H
#define IPRINTABLE_H

#include <iostream>
using namespace std;

class IPrintable
{
public:
	virtual void INPUT() = 0;
	virtual void OUTPUT() const = 0;
};

#endif