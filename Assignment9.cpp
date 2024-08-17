#include<iostream>
#include<string.h>
using namespace std;

class Dict
{
	public:
		char key[20];
		char meaning[20];
		
		Dict()
		{
			key[0]='\0';
			meaning[0]='\0';
		}
		
		bool getInput()
		{
			cout<<"\nEnter key or enter -1 to stop : ";
			cin.getline(key,20);
			if(strcmp(key,"-1")==0)
			{
				return 0;
			}
			cout<<"\nEnter meaning : ";
			cin.getline(meaning,20);
			return 1;
		}
		
		void print()
		{
			cout<<key<<"->"<<meaning<<" , ";
		}
};

class Stack
{
	public:
		Dict data[20];
		int top;
		
		Stack()
		{
			top=-1;
		}
		
		void push(Dict obj)
		{
			top++;
			data[top]=obj;
		}
		
		Dict pop()
		{
			Dict x=data[top];
			top--;
			return x;
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

class Node
{
	public:
		Dict data;
		int height;
		Node* left;
		Node *right;
		
		Node()
		{
			height=0;
			left=NULL;
			right=NULL;
		}
};

class AVL
{
	public:
		Node* root;
		Stack s;
		AVL()
		{
			root=NULL;
		}
		
		Node* rotateleft(Node* x);
		Node* rotateright(Node* x);
		Node* RR(Node* T);
		Node* LL(Node* T);
		Node* RL(Node* T);
		Node* LR(Node* T);
		int height(Node* T);
		Node* insert(Node *&c,Dict k);
		Node* balance(Node* T);
		void ascending(Node *c);
		void descending(Node* c);
		void descendingPrint();
		int Update_height(Node *c);
		int balance_factor(Node *c);
		int search(Node *c,char* key);
};

int AVL::height(Node* T)
{
	int lh=0;
	int rh=0;
	if(T->left!=NULL)
	{
		lh=1+T->left->height;
	}
	if(T->right!=NULL)
	{
		lh=1+T->right->height;
	}	
	if(lh>rh)
	{
		return lh;
	}
	return rh;
}

Node* AVL::rotateright(Node* x)
{
	Node* y=x->left;
	x->left=y->right;
	y->right=x;
	x->height=height(x);
	y->height=height(y);
	return y;
}

Node* AVL::rotateleft(Node* x)
{
	Node* y=x->right;
	x->right=y->left;
	y->left=x;
	x->height=height(x);
	y->height=height(y);
	return y;	
}

Node* AVL::RR(Node* T)
{
	T=rotateleft(T);
	return T;
}

Node* AVL::LL(Node* T)
{
	T=rotateright(T);
	return T;
}

Node* AVL::LR(Node* T)
{
	T->left=rotateleft(T->left);
	T=rotateright(T);
	return T;
}

Node* AVL::RL(Node* T)
{
	T->right=rotateright(T->right);
	T=rotateleft(T);
	return T;
}

int AVL::Update_height(Node *c)
{
    if(c==NULL)
    {
        return 0;
    }
    c->height=(max((Update_height(c->left)),(Update_height(c->right)))+1);
    return c->height;
}

int AVL::balance_factor(Node *c)
{
    if(c==NULL)
    {
        return 0;
    }
    return ((Update_height(c->left))-(Update_height(c->right)));
}

Node* AVL::balance(Node *c)
{
    if(balance_factor(c)==2)
    {
        if(balance_factor(c->left)<0)
        {
            c=LR(c);
        }
        else
        {
            c=LL(c);
        }
    }
    else if(balance_factor(c)==-2)
    {
        if(balance_factor(c->right)>0)
        {
            c=RL(c);
        }
        else
        {
            c=RR(c);
        }
    }
    Update_height(c);
    return c;
}

Node* AVL::insert(Node *&c,Dict k)
{
    if(c==NULL)
    {
        c=new Node;
        c->data=k;
        return c;
    }
    if(strcmp(k.key,c->data.key)>0)
    {
        c->right=insert(c->right,k);
    }
    else if(strcmp(k.key,c->data.key)<0)
    {
        c->left=insert(c->left,k);
    }
    //cout<<c->height<<endl;
    return balance(c);
    // return c;
}

void AVL::ascending(Node *c)
{
    if(c==NULL)
    {
        return;
    }
    ascending(c->left);
    c->data.print();
    ascending(c->right);
}

void AVL::descending(Node *c)
{
    if(c==NULL)
    {
        return;
    }
    descending(c->left);
    s.push(c->data);
    descending(c->right);
}

void AVL::descendingPrint()
{
	Dict d;
	while(!s.empty())
	{
		d=s.pop();
		cout<<d.key<<" -> "<<d.meaning<<" , ";
	}
}

int AVL::search(Node *c,char* key)
{
    if(c==NULL)
    {
        return -1;
    }
    int ans=0;
    if(strcmp(key,c->data.key)==0)
    {
        return 1+ans;
    }
    else if(strcmp(key,c->data.key)>0)
    {
        ans=1+search(c->right,key);
        return ans;
    }
    else if(strcmp(key,c->data.key)<0)
    {
        ans=1+search(c->left,key);
        return ans;
    }
}

int main()
{
	AVL obj;
	Dict x;
	char ch[20];
	bool flag;
	int choice,num;
	while(1)
	{
		cout<<"\n*************** MENU ****************";
		cout<<"\n1.Add KeyWord\n2.Display data in Ascending\n3.Display data in Descending\n4.Maximum comparisons required to find a keyword\n5.Exit";
		cout<<"\n\nEnter your choice : ";
		cout<<"\n>>>";
		cin>>choice;
		switch(choice)
		{
			case 1:
				cin.ignore(1);
				flag=x.getInput();
				obj.root=obj.insert(obj.root,x);
				break;
			case 2:	
			    cout<<"\nDATA IN ASCENDING ORDER : ";
				obj.ascending(obj.root);
				break;
			case 3:
				cout<<"\nDATA IN DESCENDING ORDER : ";
				obj.descending(obj.root);
				obj.descendingPrint();
				break;
			case 4:
				cin.ignore(1);
				cout<<"\nEnter the key to search : ";
				cin.getline(ch,20);
				num=obj.search(obj.root,ch);
				cout<<"\nNum : "<<num;
				break;
			case 5:
				cout<<"\nEXITING...";
				break;
			default:
			    break;							
		}
	}
	return 0;
}

