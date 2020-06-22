#include <iostream>
#include "Interval_Graph.h"

using namespace std;

void GreedyColoring();

int main()
{
	GreedyColoring();

	system("pause");
	return 0;
}

void GreedyColoring()
{
	int k;

	cout << "Please input k" << endl;
	cin >> k;

	Interval_Graph graph = Interval_Graph(k);
	cin >> graph;
	cout << graph;
	graph.Get_Info_About_Edges();
}