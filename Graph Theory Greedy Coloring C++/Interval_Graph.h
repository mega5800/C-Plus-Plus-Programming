#pragma once

#ifndef INTERVAL_GRAPH_H
#define INTERVAL_GRAPH_H

#include "Interval.h"
#include <iostream>
#include <cstdlib>
using namespace std;

class Interval_Graph
{
public:
	Interval_Graph();
	Interval_Graph(int);
	~Interval_Graph();

	friend istream &operator>>(istream&, Interval_Graph&);
	friend ostream &operator<<(ostream&, Interval_Graph&);

	int Get_Chrom_Num() const;

	void Get_Info_About_Edges();

private:
	int len;
	int Chrom_Num;
	Interval* arr;
	int** Neighbor_Mat;

	void Fill_Mat();

	void Set_Val_To_Mat();
	void Set_Val_To_Arr(int*, int len);

	int Get_Num_Edges();
	int Get_Edge_From_Row(int*);
	void Find_Max_Min_Deg(int*, int*);
	int Calc_K_Edges();
	int Set_Chromatic_Number();
	bool Check_Colors(int*, int);
	void Print_Interval(Interval, int, int = 0, int = 0);
	void Print_Coloring();
	int* Count_Colors();
	friend int compare(const void* a, const void* b);
};

#endif