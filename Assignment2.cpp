#include<iostream>
using namespace std;

class BSTNode
{
    public:
        int data;
        BSTNode *left;
        BSTNode *right;

        BSTNode(int d)
        {
            data=d;
            left=NULL;
            right=NULL;
        }
};


class BST
{
    public:
        BSTNode *root;
        BST()
        {
            root=NULL;
        }

        BSTNode* createBST(BSTNode *T,int x);

        void inorder(BSTNode *T);

        BSTNode* swap(BSTNode *T);

        int search(BSTNode *T,int x);

        int min_ele();

        int max_ele();

        int height(BSTNode *T);
};


BSTNode* BST::createBST(BSTNode *T,int x)
{
	if(T==NULL)
	{
		T=new BSTNode(x);
	}
	else if(x>T->data)
	{
		T->right=createBST(T->right,x);
	}
	else
	{
		T->left=createBST(T->left,x);
	}
	return T;
}


void BST::inorder(BSTNode *T)
{
	if(T!=NULL)
	{
		inorder(T->left);
		cout<<T->data<<" ";
		inorder(T->right);
	}
}

BSTNode* BST::swap(BSTNode *T)
{
    BSTNode *p;
    if(T!=NULL)
    {
        p=T->left;
        T->left=swap(T->right);
        T->right=swap(p);
    }
    return T;
}

int BST::search(BSTNode *T,int x)
{
	int ans;
	if(T==NULL)
	{
		return 0;
	}
	if(T->data==x)
	{
		return 1;
	}
	else
	{
		if(x<T->data)
		{
			ans=search(T->left,x);
			return ans;
		}
		else
		{
            ans=search(T->right,x);
		    return ans;
	    }
	}
	return 0;
}


int BST::min_ele()
{
	BSTNode *T=root;
	while(T->left!=NULL)
	{
		T=T->left;
	}
	return T->data;
}



int BST::max_ele()
{
	BSTNode *T=root;
	while(T->right!=NULL)
	{
		T=T->right;
	}
	return T->data;
}


int BST::height(BSTNode *T)
{
    int hl,hr;
    if(T==NULL)
    {
        return 1;
    }
    if(T->left==NULL && T->right==NULL)
    {
        return 1;
    }
    hl=height(T->left);
    hr=height(T->right);
    if(hl>hr)
    {
        return(hl+1);
    }
    return(hr+1);
}



int main()
{
	BST t1;
	int choice;
	while(1)
	{
		cout<<"\n***************** MENU *****************";
		cout<<"\n1.Create BST by inserting nodes";
		cout<<"\n2.Number of nodes in Longest path";
		cout<<"\n3.Minimum and Maximum data value";
		cout<<"\n4.SWap tree";
		cout<<"\n5.Search an element";
		cout<<"\n\nEnter your choice : ";
		cout<<"\n>>";
		cin>>choice;
		switch(choice)
		{
		    case 1:
		    	int num;
		    	while(1)
		    	{
		    		cout<<"\nEnter data or enter 0 to stop : ";
		    		cin>>num;
		    		if(num==0)
		    		{
		    			break;
		    		}
		    		t1.root=t1.createBST(t1.root,num);
		    	}
		    	cout<<"\nBST created successfully ...";
		    	cout<<"\nBST : ";
		    	t1.inorder(t1.root);
		    	break;
		    case 2:
		    	cout<<"\nNumber of nodes in the Longest Path : "<<t1.height(t1.root);
		    	break;
		    case 3:
		    	cout<<"\nMinimum element : "<<t1.min_ele();
		    	cout<<"\nMaximum element : "<<t1.max_ele();
		    	break;
		    case 4:
		    	t1.root=t1.swap(t1.root);
		    	cout<<"\nSwapped BST : ";
		    	t1.inorder(t1.root);
		    	break;
		    case 5:
		    	int x;
		    	cout<<"\nEnter the number you want to search : ";
		    	cin>>x;
		    	if(t1.search(t1.root,x))
		    	{
		    		cout<<"\n"<<x<<" Found in BST";
		    	}
		    	else
		    	{
		    		cout<<"\n"<<x<<" Found in BST";
		    	}
		    	break;
		    default:
		    	break;
		}
	}
}
