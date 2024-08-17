//============================================================================
// Name        : Assignment7_21414.cpp
// Author      : Diya Bhat
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

class Graph
{
public:
	int **adj_matrix;
	int **spanning_tree;
	string *city;
	int *c;
	int n;

	Graph()
	{
		cout<<"\nEnter number of cities : ";
		cin>>n;
		adj_matrix=new int*[n];
		spanning_tree=new int*[n];
		city=new string[n];
		c=new int[n];
		cin.ignore(1);
		for(int i = 0; i < n; i++)
		{
			cout<<"\nEnter city number "<<i+1<<" : ";
			getline(cin,city[i]);
			c[i]=i;
		}
		for(int i = 0; i < n; i++)
		{
			adj_matrix[i] = new int[n];
			spanning_tree[i]=new int[n]; 
		}
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				adj_matrix[i][j]=0;
				spanning_tree[i][j]=0;
			}
		}
	}

	void createGraph();
	void showGraph();
	void show_SpanningTree();
	void prims(string city);
	int findIndex(string c);
	int find_min(int *p,int *t);
};

void Graph::createGraph()
{
	int max_edges=(n*(n-1)/2);
	int origin;
	int weight;
	int destination;
	string o,d;
	for(int i=0;i<max_edges;i++)
	{
		cout<<"\nEnter origin or enter -1 to stop : ";
		getline(cin,o);
		if(o[0]=='-' && o[1]=='1')
		{
			break;
		}			
		cout<<"\nEnter destination : ";
		getline(cin,d);
		origin=findIndex(o);
		destination=findIndex(d);
		if(origin>n ||destination>n||origin<=-1||destination<=-1)
		{
			cout<<"\nInvalid edge";
			i--;
		}
		else
		{
			cout<<"\nEnter distance : ";
			cin>>weight;
			adj_matrix[origin][destination]=weight;
			adj_matrix[destination][origin]=weight;
			cin.ignore(1);
		}
	}
}

void Graph::showGraph()
{
	cout<<"\nAdjacency Matrix : "<<"\n";
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			cout<<adj_matrix[i][j]<<" ";
		}
		cout<<"\n";
	}
}

void Graph::show_SpanningTree()
{
	cout<<"\nSpanning tree Matrix : "<<"\n";
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			cout<<spanning_tree[i][j]<<" ";
		}
		cout<<"\n";
	}
}

int Graph::findIndex(string c)
{
	for(int i=0;i<n;i++)
	{
		if(city[i]==c)
		{
			return i;
		}
	}
	return -1;
}

int Graph::find_min(int *p,int *t)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		if(t[i]==0)
		{
			break;
		}
	}
	int min=i;
	for(j=min;j<n;j++)
	{
		if(p[j]<p[min] && t[j]==0)
		{
			min=j;
		}
	}
	return min;
}

void Graph::prims(string city)
{
	int min,cost=0;
	int* track=new int[n];
	int* path=new int[n];
	int *parent=new int[n];
	int min_cost=0;
	for(int i=0;i<n;i++)
	{
		track[i]=0;
		path[i]=999;
		parent[i]=-1;
	}
	int ind=findIndex(city);
	path[ind]=0;
	int j=0;
	while(j<n)
	{
		min=find_min(path,track);
		track[min]=1;
		cost+=path[min];
		for(int i=0;i<n;i++)
		{
			if(adj_matrix[min][i]!=0)
			{
				if(path[i]>=(adj_matrix[min][i]))
				{
					path[i]=adj_matrix[min][i];
					if(track[i]==0)
					{
						parent[i]=min;
					}
				}
			}			
		}
		j++;
		/*cout<<"\nPATH : ";
		for(int i=0;i<n;i++)
		{
			cout<<path[i]<<" ";
		}	
		cout<<"\nTRACK : ";
		for(int i=0;i<n;i++)
		{
			cout<<track[i]<<" ";
		}
		cout<<"\nPARENT : ";
		for(int i=0;i<n;i++)
		{
			cout<<parent[i]<<" ";
		}*/			
	}
	for(int i=0;i<n;i++)
	{
		if(parent[i]!=-1)
		{
			spanning_tree[parent[i]][i]=adj_matrix[parent[i]][i];
			spanning_tree[i][parent[i]]=adj_matrix[parent[i]][i];
		}
	}
	cout<<"\nTotal Cost of Spanning Tree = "<<cost;	
}

int main() {
	string city;
	Graph g;
	g.createGraph();
	g.showGraph();
	cout<<"\nEnter the city from where you want to start : ";
	getline(cin,city);
	g.prims(city);
	g.show_SpanningTree();
	return 0;
}
