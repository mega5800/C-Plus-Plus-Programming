#include "Interval_Graph.h"
#include "Interval.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Interval_Graph::Interval_Graph()
{
}

Interval_Graph::Interval_Graph(int l)
{
	this->len = l;
	this->Chrom_Num = 0;
	this->arr = new Interval[l];
	this->Neighbor_Mat = new int*[l];

	for (int i = 0; i < l; i++)
		this->Neighbor_Mat[i] = new int[l];
	Set_Val_To_Mat();
}

Interval_Graph::~Interval_Graph()
{
	delete[]this->arr;

	for (int i = 0; i < this->len; i++)
		delete[]this->Neighbor_Mat[i];
	delete[]this->Neighbor_Mat;
}

int Interval_Graph::Get_Chrom_Num() const
{
	return this->Chrom_Num;
}

int compare(const void * a, const void * b)
{
	const Interval* x = (Interval*)a;
	const Interval* y = (Interval*)b;
	if (x->Get_Start() > y->Get_Start())
		return 1;
	else
		if (x->Get_Start() < y->Get_Start())
			return -1;
	return 0;
}

void Interval_Graph::Get_Info_About_Edges()
{
	qsort(this->arr, this->len, sizeof(Interval), compare);
	cout << *this;
	Fill_Mat();
	int max = 0, min = 0, num_edges = Get_Num_Edges();
	cout << "G Edges = " << num_edges << endl;
	Find_Max_Min_Deg(&max, &min);
	cout << "Maximum Degree of G = " << max << endl;
	cout << "Minumum Degree of G = " << min << endl;
	this->Chrom_Num = Set_Chromatic_Number();
	cout << "Chromatic Number of G = " << this->Chrom_Num << endl;
	cout << "G's Complement Edges = " << Calc_K_Edges() - num_edges << endl;
	cout << "Maximum Degree of G's Complement = " << this->len - min - 1 << endl;
	cout << "Minumum Degree of G's Complement = " << this->len - max - 1 << endl;
	Print_Coloring();
}

void Interval_Graph::Fill_Mat()
{
	bool is_there_edge = false;
	float bi, fi, bn, fn;
	int i, n, len = this->len;

	for (i = 0; i < len; i++)
	{
		bi = this->arr[i].Get_Start();
		fi = this->arr[i].Get_End();

		for (n = 0; n < len; n++)
		{
			if (n == i)
				continue;

			bn = this->arr[n].Get_Start();
			fn = this->arr[n].Get_End();

			if ((bi <= bn) && (bn <= fi) && (fi <= fn))
				is_there_edge = true;
			else
				if ((bn <= bi) && (bi <= fn) && (fn <= fi))
					is_there_edge = true;
				else
					if ((bi <= bn) && (fn <= fi))
						is_there_edge = true;
					else
						if ((bn <= bi) && (fi <= fn))
							is_there_edge = true;

			if (is_there_edge)
			{
				this->Neighbor_Mat[i][n] = 1;
				this->Neighbor_Mat[n][i] = 1;
				is_there_edge = false;
			}
		}
	}
}

int Interval_Graph::Get_Num_Edges()
{
	int i, sum = 0;
	for (i = 0; i < this->len; i++)
		sum += Get_Edge_From_Row(this->Neighbor_Mat[i]);

	return sum / 2;
}

int Interval_Graph::Get_Edge_From_Row(int *row)
{
	int i, sum = 0;
	for (i = 0; i < this->len; i++)
		sum += row[i];

	return sum;
}

void Interval_Graph::Find_Max_Min_Deg(int *max_ptr, int *min_ptr)
{
	int i, len = this->len, max, min, tmp;
	max = min = Get_Edge_From_Row(this->Neighbor_Mat[0]);

	for (i = 1; i < len; i++)
	{
		tmp = Get_Edge_From_Row(this->Neighbor_Mat[i]);
		if (tmp > max)
			max = tmp;
		if (tmp < min)
			min = tmp;
	}

	*max_ptr = max;
	*min_ptr = min;
}

int Interval_Graph::Calc_K_Edges()
{
	int res = this->len*(this->len - 1);
	return res / 2;
}

int Interval_Graph::Set_Chromatic_Number()
{
	int i, Max_Chromatic_Number = 0, color = 1;

	for (i = 0; i < this->len; i++)
	{
		while (!Check_Colors(this->Neighbor_Mat[i], color))
			color++;

		this->arr[i].Set_Color(color);

		if (color > Max_Chromatic_Number)
			Max_Chromatic_Number = color;
		color = 1;
	}

	return Max_Chromatic_Number;
}

bool Interval_Graph::Check_Colors(int *row, int color)
{
	for (int i = 0; i < this->len; i++)
		if (row[i] != 0)
			if (this->arr[i].Get_Color() == color)
				return false;
	return true;
}

void Interval_Graph::Print_Interval(Interval inter, int i, int color, int count_color)
{
	if ((color != 0) && (inter.Get_Color() != color))
		return;

	inter.Print();
	
	if ((color == 0) && (i == len - 1))
		return;
	if ((color != 0) && (count_color == 0))
		return;

	cout << ",";
}

void Interval_Graph::Print_Coloring()
{
	int i, n, *color_count = Count_Colors(), n_color;
	cout << "Optional Coloring: ";

	for (i = 0; i < this->Chrom_Num; i++)
	{
		cout << "{";
		for (n = 0; n < this->len; n++)
		{
			n_color = this->arr[n].Get_Color();
			if (n_color - 1 == i)
			{
				color_count[n_color - 1]--;
				Print_Interval(this->arr[n], n, i + 1, color_count[n_color - 1]);
			}
		}
		cout << "} - " << i + 1;
		if (i != this->Chrom_Num - 1)
			cout << ", ";
	}
	cout << endl;

	delete[]color_count;
}

int * Interval_Graph::Count_Colors()
{
	int *res = new int[this->Chrom_Num];
	Set_Val_To_Arr(res, this->Chrom_Num);

	for (int i = 0; i < this->len; i++)
		res[this->arr[i].Get_Color() - 1]++;

	return res;
}

void Interval_Graph::Set_Val_To_Mat()
{
	for (int i = 0; i < this->len; i++)
		Set_Val_To_Arr(this->Neighbor_Mat[i], this->len);
}
void Interval_Graph::Set_Val_To_Arr(int *arr, int len)
{
	for (int i = 0; i < len; i++)
		arr[i] = 0;
}

istream & operator>>(istream &cin, Interval_Graph &graph)
{
	float s, e;
	int len = graph.len, i;

	cout << "You will now be asked to insert a family of " << len << " intervals:" << endl;

	for (i = 0; i < len; i++)
	{
		cout << i + 1 << "th interval: ";
		cin >> s >> e;

		graph.arr[i].Set_Start(s);
		graph.arr[i].Set_End(e);
	}

	return cin;
}
ostream & operator<<(ostream &cout, Interval_Graph &graph)
{
	int i, len = graph.len;
	cout << "The Intervals family is:" << endl;
	for (i = 0; i < len; i++)
		graph.Print_Interval(graph.arr[i], i);
	cout << endl;
	return cout;
}