#include <iostream>
using namespace std;

class Node
{
	public:
		int data;
		Node *llink;
		Node*rlink;
		int lbit;
		int rbit;

	Node()
	{
		data=0;
		llink=rlink=NULL;
		lbit=rbit=0;
	}
	
	Node(int d)
	{
		data=d;
		llink=rlink=NULL;
		lbit=rbit=0;
	}
	
	~Node()
	{
		cout<<"\nNode Deleted...";
	}
};



class Queue
{
	Node* data[20];
	int front;
	int rear;
	
	public:
	
	Queue()
	{
		front=rear=-1;
	}
	
	void enqueue(Node* d)
	{
		if(front==-1)
		{
			front++;
			rear++;
			data[rear]=d;
		}
		else
		{
			rear++;
			data[rear]=d;
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
	
	Node* dequeue()
	{
		Node* temp;
		if(front==rear)
		{
			temp=data[front];
			front=rear=-1;
			return temp;
		}
		temp=data[front];
		front++;
		return temp;
	}
};


class TBT
{
	Node *head;
	
	public:
	void create();
	void Linsert(Node* s,Node *t);
	void Rinsert(Node* s,Node *t);
	void preorder(Node *head);
	void inorder(Node *head);
	Node* insuc(Node *x);
	void DeleteTBT(Node *parent,Node *child);
	friend int main();
};



void TBT::create()
{
	head=new Node(0);
	head->lbit=0;
	head->rbit=1;
	head->llink=head;
	head->rlink=head;
	Queue Q;
	Node* temp;
	int data;
	Node * x;
	Q.enqueue(head);
	while(Q.empty()==0)
	{
		temp=Q.dequeue();
		cout<<"\nEnter left data for "<<temp->data<<" : ";
		cin>>data;
		if(data!=0)
		{
			x=new Node(data);
			Linsert(temp,x);
			Q.enqueue(x);
		}
		if(temp!=head)
		{
			cout<<"\nEnter right data for "<<temp->data<<" : ";
			cin>>data;
			if(data!=0)
			{
				x=new Node(data);
				Rinsert(temp,x);
				Q.enqueue(x);
			}
		}
	}
}



void TBT::Linsert(Node* s,Node *t)
{
	t->llink=s->llink;
	t->lbit=s->lbit;
	t->rlink=s;
	t->rbit=0;
	s->llink=t;
	s->lbit=1;
}



void TBT::Rinsert(Node* s,Node *t)
{
	t->rlink=s->rlink;
	t->rbit=s->rbit;
	t->llink=s;
	t->lbit=0;
	s->rlink=t;
	s->rbit=1;
}



void TBT::preorder(Node *head)
{
	cout<<"\nPreorder Traversal : ";
	int flag=1;
	Node *p=head->llink;
	while(p!=head)
	{
		while(flag!=0)
		{
			cout<<p->data<<" ";
			if(p->lbit==1)
			{
				p=p->llink;
			}
			else
			{
				break;
			}
		}
		flag=p->rbit;
		p=p->rlink;
	}
}



Node* TBT::insuc(Node *x)
{
	Node*s=x->rlink;
	if(x->rbit==1)
	{
		while(s->lbit==1)
		{
			s=s->llink;
		}
	}
	return s;
}


void TBT::inorder(Node *head)
{
	cout<<"\nInorder Traversal : ";
	Node* T=head;
	while(1)
	{
		T=insuc(T);
		if(T==head)
		{
			return;
		}
		cout<<T->data<<" ";
	}
}

void TBT::DeleteTBT(Node* parent,Node* child)
{
    Node* child_succ;
    if(child->lbit == 1 && child->rbit == 1)
    {
        parent=child;
        child_succ=child->rlink;
        while(child_succ->lbit !=0)
        {
            parent=child_succ;
            child_succ=child_succ->llink;
        }
        child->data=child_succ->data;
        child=child_succ;
    }
    if(child->lbit == 0 && child->rbit==0)
    {
        if(parent->rlink == child)
        {
            parent->rlink=child->rlink;
            parent->rbit=child->rbit;
        }
        else
        {
            parent->llink=child->llink;
            parent->lbit=child->lbit;
        }
        delete(child);
        return;
    }
    if(child->lbit == 1 && child->rbit == 0)
    {
        if(parent->llink == child)
        {
            parent->llink=child->llink;
            parent=parent->llink;
        }
        else
        {
            parent->rlink=child->llink;
            parent=parent->rlink;
        }
        while(parent->rbit == 1)
        {
            parent=parent->rlink;
        }
        parent->rlink=child->rlink;
        delete(child);
    }
    if(child->lbit == 0 && child->rbit == 1)
    {
        if(parent->llink==child)
        {
            parent->llink=child->rlink;
            parent=parent->llink;
        }
        else
        {
            parent->rlink=child->rlink;
            parent=parent->rlink;
            while(parent->lbit == 1)
            {
                parent=parent->llink;
            }
            parent->llink=child->llink;
            delete(child);
            return;
        }
    }
}



int main()
{
	TBT t1;
    int choice;
    Node* child =NULL;
    Node* parent=NULL ;
	while(1)
	{
		cout<<"\n***************** MENU *******************";
		cout<<"\n1.Create Threaded Binary Tree";
		cout<<"\n2.Show Preorder Traversal";
		cout<<"\n3.Show Inorder Traversal";
		cout<<"\n4.Delete in TBT";
		cout<<"\n5.Exit";
		cout<<"\n\nEnter your choice : ";
		cout<<"\n>>>";
		cin>>choice;
		switch(choice)
		{
			case 1:
				t1.create();
				cout<<"\nThreaded Binary Tree created successfully...";
				break;
			case 2:
				t1.preorder(t1.head);
				break;
			case 3:
				t1.inorder(t1.head);
				break;
			case 4:
				int value;
				cout<<"Enter the value to delete : "<<endl;
				cin>>value;
				parent = NULL;
				child = t1.head->llink;
				while (child != t1.head) 
				{
				   if (value < child->data) 
				   {
				       if (child->lbit == 0)
					    {
				           break;
				        }
				       parent = child;
				       child = child->llink;
				   }
				   else if (value > child->data) 
				   {
				       if (child->rbit == 0) 
					   {
				           break;
				       }
				       parent = child;
				       child = child->rlink;
				   } 
				   else 
				   {
				       t1.DeleteTBT(parent, child);
				   }
				}
			    break;
			case 5:
				cout<<"\nExiting...";
				break;
		}
	}
	return 0;
}
