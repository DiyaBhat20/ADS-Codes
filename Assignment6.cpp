//============================================================================
// Name        : Assignment6_21414.cpp
// Author      : Diya Bhat
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string.h>
using namespace std;

class Node
{
    public:
		int data;
		Node *next;
		
		Node()
		{
			data=0;
			next=NULL;
		}
		
		Node(int d)
		{
			data=d;
			next=NULL;
		}
};

class Stack
{
public:
	Node* data[20];
	int top;
	Stack()
	{
		top=-1;
	}

	void push(Node *d)
	{
		if(top==19)
		{
			cout<<"\nStack Full";
			return;
		}
		top++;
		data[top]=d;
	}

	Node* pop()
	{
		if(top==-1)
		{
			return NULL;
		}
		Node *t=data[top];
		top--;
		return t;
	}

	int empty()
	{
		if(top==-1)
		{
			return 1;
		}
		return 0;
	}
};

class Queue
{
public:
	Node* data[20];
	int front,rear;
	Queue()
	{
		front=rear=-1;
	}

	void enqueue(Node* d)
	{
		if(front==-1)
		{
			front=rear=0;
			data[front]=d;
		}
		else
		{
			rear++;
			data[rear]=d;
		}
	}

	Node* dequeue()
	{
		if(front==-1)
		{
			return NULL;
		}
		else if(front==rear)
		{
			Node *t=data[front];
			front=rear=-1;
			return t;
		}
		else
		{
			Node *temp=data[front];
			front++;
			return temp;
		}
	}

	int empty()
	{
		if(front==-1)
		{
			return 1;
		}
		return 0;
	}
};

class Graph
{
public:
	Node** head;
	int vertices;
	int* visit;
	string* landmarks;

public:
	Graph()
	{
		string a;
		cout<<"\nEnter number of landmarks : ";
		cin>>vertices;
		landmarks=new string[vertices];
		visit=new int[vertices];
		head=new Node*[vertices];
		cin.ignore(1);
		for(int i=0;i<vertices;i++)
		{
			while(1)
			{
				cout<<"\nEnter area "<<i+1<<" : ";
				getline(cin,a);
				int j=i-1;	
				while(j>=0)
				{
					if(landmarks[j]==a)
					{
						cout<<"\nLandmark already added !";
						i--;
						break;
					}
					j--;
				}
				break;				
			}
			head[i]=new Node(i);
			landmarks[i]=a;
			visit[i]=0;
		}
	}

	int findIndex(string c)
	{
		for(int i=0;i<vertices;i++)
		{
			if(landmarks[i]==c)
			{
				return i;
			}
		}
		return -1;
	}
	
	int check(int i,string l)
	{
		Node* T=head[i]->next;
		while(T!=NULL)
		{
			if(landmarks[T->data]==l)
			{
				return 1;
			}
			T=T->next;
		}
		return 0;
	}

	void createGraph()
	{
		Node *p=NULL;
		int no;
		int vno;
		string v;
		for(int i=0;i<vertices;i++)
		{
			p=head[i];
			int lno=findIndex(landmarks[i]);
			while(1)
			{
				cout<<"\nEnter the number of landmarks which are adjacent to "<<landmarks[i]<<" : ";
				cin>>no;	
				if(no<0 || no>=vertices)
				{
					cout<<"\nInvalid Input !";
				}
				else
				{
					break;
				}			
			}
			cin.ignore(1);
			if(no!=0 && no<vertices)
			{
				for(int j=0;j<no;j++)
				{
					cout<<"\nEnter the adjacent landmarks : ";
					getline(cin,v);
					if(check(i,v)==0)
					{
						Node *t=new Node;
						vno=findIndex(v);
						t->data=vno;
						if(vno==lno||vno<0||vno>vertices)
						{
							cout<<"\nInvalid landmark";
							j--;
						}
						else
						{
							p->next=t;
							p=p->next;
						}
					}
					else
					{
						cout<<"\nLandmark already added !";
						j--;
					}
				}
			}
		}
	}

	void showGraph()
	{
		Node *p=NULL;
		cout<<"\nGRAPH : ";
		for(int i=0;i<vertices;i++)
		{
			if(head[i]->next==NULL)
			{
				cout<<"\n"<<landmarks[head[i]->data];
			}
			else
			{
				cout<<"\n"<<landmarks[head[i]->data]<<" -> ";
				p=head[i]->next;
				while(p->next!=NULL)
				{
					cout<<landmarks[p->data]<<" -> ";
					p=p->next;
				}
				cout<<landmarks[p->data];
			}
		}
	}

	void DFS_recursive(int vno)
	{
		Node *temp;
		if(visit[vno]==0)
		{
			cout<<landmarks[head[vno]->data]<<" -> ";
			visit[vno]=1;
		}
		temp=head[vno]->next;
		while(temp!=NULL)
		{
			int t=temp->data;
			if(visit[t]==0)
			{
				DFS_recursive(t);
			}
			temp=temp->next;
		}
	}

	void clearArray()
	{
		for(int i=0;i<vertices;i++)
		{
			visit[i]=0;
		}
	}

	void DFS(int vno)
	{
		Stack s;
		Node *temp=head[vno];
		s.push(temp);
		while(s.empty()==0)
		{
			Node *p=s.pop();
			if(visit[p->data]==0)
			{
				cout<<landmarks[p->data]<<" -> ";
				visit[p->data]=1;
				p=head[p->data]->next;
				while(p!=NULL)
				{
					if(visit[p->data]==0)
					{
						s.push(p);
					}
					p=p->next;
				}
			}
		}
	}

	void BFS(int vno)
	{
		Queue q;
		Node *temp=NULL;
		visit[vno]=1;
		cout<<landmarks[head[vno]->data]<<" -> ";
		q.enqueue(head[vno]);
		while(!q.empty())
		{
			temp=q.dequeue();
			temp=temp->next;
			while(temp!=NULL)
			{
				if(visit[temp->data]==0)
				{
					q.enqueue(head[temp->data]);
					cout<<landmarks[temp->data]<<" -> ";
					visit[temp->data]=1;
				}
				temp=temp->next;
			}
		}
	}

};

int main() {
	Graph g;
	int choice;
	string lm;
	int num;
	while(1)
	{
		cout<<"\n**************** MENU *******************";
		cout<<"\n1.Create Graph";
		cout<<"\n2.Show Graph";
		cout<<"\n3.DFS Recursive";
		cout<<"\n4.DFS using Stack";
		cout<<"\n5.BFS using Queue";
		cout<<"\n6.Exit";
		cout<<"\nEnter your choice : ";
		cout<<"\n>>>";
		cin>>choice;
		switch(choice)
		{
		case 1:
			g.createGraph();
			break;
		case 2:
			g.showGraph();
			break;
		case 3:
			cin.ignore(1);
			cout<<"\nEnter the landmark to start : ";
			getline(cin,lm);
			num=g.findIndex(lm);
			if(num!=-1)
			{
				cout<<"\nDFS using Recursion : ";
				g.DFS_recursive(num);
				g.clearArray();
			}
			else
			{
				cout<<"\nInvalid Landmark";
			}
			break;
		case 4:
			cin.ignore(1);
			cout<<"\nEnter the landmark to start : ";
			getline(cin,lm);
			num=g.findIndex(lm);
			if(num!=-1)
			{
				cout<<"\nDFS using Stack : ";
				g.DFS(num);
				g.clearArray();
			}
			else
			{
				cout<<"\nInvalid Landmark";
			}
			break;
		case 5:
			cin.ignore(1);
			cout<<"\nEnter the landmark to start : ";
			getline(cin,lm);
			num=g.findIndex(lm);
			if(num!=-1)
			{
				cout<<"\nBFS using Queue : ";
				g.BFS(num);
				g.clearArray();
			}
			else
			{
				cout<<"\nInvalid Landmark";
			}
			break;
		case 6:
			cout<<"\nExiting...";
			break;
		}
	}
	return 0;
}#include<iostream>
using namespace std;

int main()
{
	return 0;
}

