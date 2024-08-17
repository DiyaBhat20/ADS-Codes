#include <iostream>
#include<string.h>
using namespace std;

class Node
{
	public:
		char ch[20];
		Node *next;
	
	Node()
	{
		ch[0]='\0';
		next=NULL;
	}
	
	Node(char *c)
	{
		strcpy(ch,c);
		next=NULL;
	}
	
	~Node()
	{
	    cout<<"\nNode deleted successfully";
	}
};

class Hash
{
	Node *arr[26];
	public:
		Hash()
		{
			for(int i=0;i<26;i++)
			{
				Node *nnode=new Node();
				char c[2]={'a'+i,'\0'};
				strcpy(nnode->ch,c); 
				arr[i]=nnode;
				nnode->next=NULL;
			}
		}
		
		void show()
		{
			for(int i=0;i<26;i++)
			{
				char* temp=arr[i]->ch;
				Node *p=arr[i];
				while(p!=NULL)
				{
					cout<<"("<<temp<<" , "<<p->ch<<")"<<" -> ";
					p=p->next;
				}
				cout<<"\n";
			}
		}
		
		void insert(char key,char *value)
		{
			int k=key-'a';
			Node *nnode=new Node(value);
			if(arr[k]->next==NULL)
			{
			    arr[k]->next=nnode;
			}
			else
			{
			    Node *p=arr[k];
			    while(p->next!=NULL)
			    {
			        p=p->next;
			    }
			    p->next=nnode;
			}
		}
		
		int find(char key,char *value)
		{
			int k=key-'a';
			Node *p=arr[k];
			while(p!=NULL)
			{
				if(strcmp(p->ch,value)==0)
				{
			        return 1;
				}
				p=p->next;
			}
			return 0;
		}
		
		void delete_(char key,char *value)
		{
			int k=key-'a';
			Node *p=arr[k];
			while(p!=NULL)
			{
			    if(strcmp(p->next->ch,value)==0)
			    {
			        break;
			    }
			    p=p->next;
			}
			Node *q=p->next;
			p->next=q->next;
			delete q;
		}
};

int main() {
	Hash h;
	int choice;
	char str[20];
	char c;
	while(1)
	{
		cout<<"\n************* MENU **************";
		cout<<"\n1.Insert";
		cout<<"\n2.Show";
		cout<<"\n3.Find";
		cout<<"\n4.Delete";
		cout<<"\nEnter your choice : ";
		cin>>choice;
		switch (choice)
		{
			case 1:
				cout<<"\nEnter string : ";
				cin.ignore(1);
				cin.getline(str,20);
				h.insert(str[0],str);
			break;
			case 2:
		    	h.show();
			    break;
			case 3:
				cin.ignore(1);
				cout<<"\nEnter key to find : ";
				cin>>c;
				cout<<"\nEnter value to find : ";
				cin.ignore(1);
				cin.getline(str,20);
				if(h.find(c,str))
				{
				cout<<"\n"<<str<<" found !";
				}
				else
				{
				cout<<"\n"<<str<<" not found !";
				}
				break;
			case 4:
				cin.ignore(1);
				cout<<"\nEnter key to delete : ";
				cin>>c;
				cout<<"\nEnter value to delete : ";
				cin.ignore(1);
				cin.getline(str,20);
				h.delete_(c,str);
				break;
		}
	}
	return 0;
}
