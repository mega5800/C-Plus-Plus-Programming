#pragma once

#include <iostream>
#include<vector>
#include "Shape.h"
#include "Line.h"
#include"Circle.h"
#include <algorithm>

using namespace std;

class Graph_Matrix
{
public:
	Graph_Matrix();
	Graph_Matrix(int, vector<Line*>& );
	virtual ~Graph_Matrix();

	void Update_Mat(vector<Line*>&);
	void Rebuild_Mat(int, vector<Line*>& l);
	int Get_Num_Edges();
	void Find_Max_Min_Deg(int*, int*);
	void Find_Max_Clique(unsigned int*,vector<int>&);
	void Write_File();
private:
	vector<vector<int>> mat;
	int length;

	void Zero();
	void Resize_Mat(vector<Line*>& l);
	int Get_Edge_From_Row(vector<int>);

	static void maximum_clique_recursive(const unsigned int **, unsigned int ,
		unsigned int *, unsigned int *, unsigned int *,
		unsigned int *, unsigned int );
	unsigned int maximum_clique(const unsigned int **, unsigned int, unsigned int **);
};