#include "stdafx.h"
#include "Graph_Matrix.h"
#include <iostream>
#include<vector>
#include "Shape.h"
#include "Line.h"
#include "Circle.h"
#include <algorithm>
#include <string>
#include <set>
#include <iterator>
#include <vector>
#include <fstream>

using namespace std;

struct node 
{
	string person;
	set<node*> friends;
	node(string p_) : person(p_) {};
	node(string p_, set<node*> f_) : person(p_), friends(f_) {};
};
ofstream myfile;

class graph
{
private:
	set<node*> g;
public:

	void addNode(string p_) 
	{
		node* n = new node(p_);
		g.insert(n);
	}

	void addEdge(string p1_, string p2_) 
	{
		node* n1 = NULL, *n2 = NULL;
		for (auto p : g) {
			if (p->person == p1_) { n1 = p; }
			else if (p->person == p2_) { n2 = p; }
		}
		if (n1 && n2)
			n1->friends.insert(n2), n2->friends.insert(n1);
	}

	set<node*> getUniverse() 
	{
		return g;
	}
};

void set_print(set<node*> s) 
{
	myfile << "[ ";
	for (auto p : s)
		myfile << p->person << " ";
	myfile << "]\n";
}

set<node*> set_union(set<node*> a, set<node*> b) 
{
	set<node*> c;
	set_union(a.begin(), a.end(), b.begin(), b.end(), inserter(c, c.end()));
	return c;
}

set<node*> set_intersection(set<node*> a, set<node*> b) 
{
	set<node*> c;
	set_intersection(a.begin(), a.end(), b.begin(), b.end(), inserter(c, c.end()));
	return c;
}

set<node*> set_difference(set<node*> a, set<node*> b) 
{
	set<node*> c;
	set_difference(a.begin(), a.end(), b.begin(), b.end(), inserter(c, c.end()));
	return c;
}

void bronKerbosch(set<node*> R, set<node*> P, set<node*> X) 
{
	if (P.empty() && X.empty()) 
	{
		set_print(R);
	}
	set<node*>::iterator v = P.begin();
	while (!P.empty() && v != P.end()) 
	{
		set<node*> singleton = { (*v) };
		bronKerbosch(set_union(R, singleton), set_intersection(P, (*v)->friends), set_intersection(X, (*v)->friends));
		P = set_difference(P, singleton);
		X = set_union(X, singleton);
		if (!P.empty())
			v = P.begin();
	}
}

Graph_Matrix::Graph_Matrix()
{
}

Graph_Matrix::Graph_Matrix(int i, vector<Line*>& l)
{
	this->length = i;
	Resize_Mat(l);
}

Graph_Matrix::~Graph_Matrix()
{
	for (int i = 0; i < this->length; i++)
		this->mat[i].clear();
	this->mat.clear();
}

void Graph_Matrix::Update_Mat(vector<Line*>& l)
{
	Zero();
	int index_1, index_2;
	vector<Line*>::iterator i = l.begin();
	for (; i != l.end(); i++)
	{
		index_1 = (*i)->c_one->index - 1;
		index_2 = (*i)->c_two->index - 1;

		this->mat[index_1][index_2]++;
		this->mat[index_2][index_1]++;
	}
}

void Graph_Matrix::Rebuild_Mat(int len, vector<Line*>& l)
{
	this->length = len;
	Resize_Mat(l);
}

void Graph_Matrix::Zero()
{
	for (int j = 0; j < this->length; j++)
		for (int n = 0; n < this->length; n++)
			this->mat[j][n] = 0;
}

void Graph_Matrix::Resize_Mat(vector<Line*>& l)
{
	this->mat.resize(this->length);
	for (int k = 0; k < this->length; k++)
		this->mat[k].resize(this->length);

	Update_Mat(l);
}

int Graph_Matrix::Get_Num_Edges()
{
	int sum = 0;
	for (int i = 0; i < this->length; i++)
		sum += Get_Edge_From_Row(this->mat[i]);

	return sum / 2;
}

void Graph_Matrix::Find_Max_Min_Deg(int *max_ptr, int *min_ptr)
{
	int i, len = this->mat.size(), max, min, tmp;
	max = min = Get_Edge_From_Row(this->mat[0]);

	for (i = 1; i < len; i++)
	{
		tmp = Get_Edge_From_Row(this->mat[i]);
		if (tmp > max)
			max = tmp;
		if (tmp < min)
			min = tmp;
	}

	*max_ptr = max;
	*min_ptr = min;
}

int Graph_Matrix::Get_Edge_From_Row(vector<int> row)
{
	unsigned int i, sum = 0;
	for (i = 0; i < this->mat.size(); i++)
		sum += row[i];

	return sum;
}

void Graph_Matrix::Find_Max_Clique(unsigned int *res, vector<int> &vec_arr)
{
	unsigned int i, n;
	const unsigned int order = this->length;
	unsigned int **r = new unsigned int*[order];

	for (i = 0; i < order; i++)
	{
		r[i] = new unsigned int[order];
		for (n = 0; n < order; n++)
			r[i][n] = this->mat[i][n];
	}

	const unsigned int **adjmat = new const unsigned int*[order];
	for (i = 0; i < order; i++)
		adjmat[i] = r[i];

	unsigned int *max_clique;
	*res = maximum_clique(adjmat, order, &max_clique);

	for (i = 0; i < order; i++)
		if (max_clique[i] == 1)
			vec_arr.push_back(i);

	for (i = 0; i < order; i++)
		free(r[i]);
	free(adjmat);
	free(r);
}

void Graph_Matrix::Write_File()
{
	graph g;
	myfile.open("cliques.txt");

	for (unsigned int i = 0; i < this->mat.size(); i++)
		g.addNode(to_string(i + 1));

	for (unsigned int i = 0; i < this->mat.size(); i++)
		for (unsigned int n = 0; n < this->mat.size(); n++)
			if (mat[i][n] == 1)
				g.addEdge(to_string(i + 1), to_string(n + 1));

	set<node*> R, P, X;
	P = g.getUniverse();
	bronKerbosch(R, P, X);
	myfile.close();
}

void Graph_Matrix::maximum_clique_recursive(const unsigned int **adjmat, unsigned int order,
	unsigned int *current_clique, unsigned int *current_clique_size, unsigned int *max_clique,
	unsigned int *max_clique_size, unsigned int level)
{
	unsigned int i, connected;
	if (level == order) 
	{
		memcpy(max_clique, current_clique, order * sizeof(unsigned int));
		*max_clique_size = *current_clique_size;
		return;
	}

	connected = 1;
	for (i = 0; i < level && connected; i++) 
	{
		if (current_clique[i] && !adjmat[level][i]) 
		{
			connected = 0;
		}
	}

	if (connected) 
	{
		current_clique[level] = 1;
		(*current_clique_size)++;
		maximum_clique_recursive(adjmat, order, current_clique, current_clique_size, max_clique,
			max_clique_size, level + 1);
		(*current_clique_size)--;
	}

	if (*current_clique_size + order - level > *max_clique_size) 
	{
		current_clique[level] = 0;
		maximum_clique_recursive(adjmat, order, current_clique, current_clique_size, max_clique,
			max_clique_size, level + 1);
	}
}

unsigned int Graph_Matrix::maximum_clique(const unsigned int **adjmat, unsigned int order, unsigned int **max_clique)
{
	unsigned int max_clique_size = 0;
	unsigned int current_clique_size = 0;
	unsigned int *current_clique = new unsigned int[order];
	*max_clique = new unsigned int[order];

	if (current_clique == NULL || *max_clique == NULL) 
	{
		free(current_clique);
		free(max_clique);
		return 0;
	}
	maximum_clique_recursive(adjmat, order, current_clique, &current_clique_size, *max_clique, &max_clique_size, 0);
	free(current_clique);
	return max_clique_size;
}