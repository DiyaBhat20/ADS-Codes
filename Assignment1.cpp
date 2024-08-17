#include<iostream>
using namespace std;

class Node
{
    public:
        int data;
        Node *left;
        Node *right;

        Node(int d)
        {
            data=d;
            left=NULL;
            right=NULL;
        }
};

class Stack
{
    public:
        Node* data[30];
        int top;

        Stack()
        {
            top=-1;
        }

        void push(Node *p)
        {
            data[++top]=p;
        }

        Node* pop()
        {
            return(data[top--]);
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

class Tree
{
    public:
        Node *root;
        Tree()
        {
            root=NULL;
        }

        Node * create();
        void preorder_rec(Node *T);
        void inorder_rec(Node *T);
        void postorder_rec(Node *T);
        void preorder();
        void inorder();
        void postorder();
        Node * swap(Node *T);
        Node * copy(Node *T);
        int height(Node *p);
        int count_leaf(Node *T);
        int count_internal(Node *T);
        Node * makeempty(Node *T);
};

Node* Tree::create()
{
    int x;
    cout<<"\nEnter data or enter -1 for no data : ";
    cin>>x;
    
    if(x==-1)
    {
        return NULL;
    }
    Node *p=new Node(x);
    cout<<"\nEnter the left child of "<<x<<" : ";
    p->left=create();
    cout<<"\nEnter the right child of "<<x<<" : ";
    p->right=create();   
    return p; 
}

void Tree::preorder_rec(Node *T)
{
    if(T!=NULL)
    {
        cout<<T->data<<" ";
        preorder_rec(T->left);
        preorder_rec(T->right);
    }
}

void Tree::inorder_rec(Node *T)
{
    if(T!=NULL)
    {
        inorder_rec(T->left);
        cout<<T->data<<" ";
        inorder_rec(T->right);
    }
}

void Tree::postorder_rec(Node *T)
{
    if(T!=NULL)
    {
        postorder_rec(T->left);
        postorder_rec(T->right);
        cout<<T->data<<" ";
    }    
}

void Tree::preorder()
{
    Stack s;
    Node *T=root;
    while(T!=NULL)
    {
        cout<<T->data<<" ";
        s.push(T);
        T=T->left;
    }
    while(!s.empty())
    {
        T=s.pop();
        T=T->right;
        while(T!=NULL)
        {
            cout<<T->data<<" ";
            s.push(T);
            T=T->left;
        }
    }
}

void Tree::inorder()
{
    Stack s;
    Node *T=root;
    while(T!=NULL)
    {
        s.push(T);
        T=T->left;
    }
    while(!s.empty())
    {
        T=s.pop();
        cout<<T->data<<" ";
        T=T->right;
        while(T!=NULL)
        {
            s.push(T);
            T=T->left;
        }
    }
}

void Tree::postorder()
{
    Stack s1, s2;
    Node *T = root;

    if (T != NULL)
        s1.push(T);

    while (!s1.empty())
    {
        T = s1.pop();
        s2.push(T);

        if (T->left != NULL)
            s1.push(T->left);

        if (T->right != NULL)
            s1.push(T->right);
    }

    while (!s2.empty())
    {
        T = s2.pop();
        cout << T->data << " ";
    }
}

Node* Tree::swap(Node *T)          //mirror
{
    Node *p;
    if(T!=NULL)
    {
        p=T->left;
        T->left=swap(T->right);
        T->right=swap(p);
    }
    return T;
}

Node* Tree::copy(Node *T)
{
    Node *p=NULL;
    if(T!=NULL)
    {
        p=new Node(T->data);
        p->left=copy(T->left);
        p->right=copy(T->right);
    }
    return p;
}

int Tree::height(Node *T)
{
    int hl,hr;
    if(T==NULL || (T->left==NULL && T->right==NULL))
    {
        return 0;
    }
    hl=height(T->left);
    hr=height(T->right);
    if(hl>hr)
    {
        return(hl+1);
    }
    return(hr+1);
}

int Tree::count_leaf(Node *T)
{
    int c;
    if(T==NULL)
    {
        return 0;
    }
    if(T->left==NULL && T->right==NULL)
    {
        return 1;
    }
    c=count_leaf(T->left)+count_leaf(T->right);
    return c;
}

int Tree::count_internal(Node *T)
{
    int c = 0;
    if (T == NULL)
    {
        return 0;
    }
    if (T->left != NULL || T->right != NULL)
    {
        c = 1;
    }
    c =c+count_internal(T->left);
    c =c+count_internal(T->right);
    return c;
}

Node* Tree::makeempty(Node *T)
{
    if(T!=NULL)
    {
        makeempty(T->left);
        makeempty(T->right);
        delete T;
    }
    return NULL;
}

int main()
{
    Tree obj;
    Tree obj2;
    obj.root=obj.create();
    int choice;  
    while(1)
    {
        cout<<"\n************** MENU **************";
        cout<<"\n1.Recursive Preorder Traversal";
        cout<<"\n2.Recursive Inorder Traversal";
        cout<<"\n3.Recursive Postorder Traversal";
        cout<<"\n4.Preorder Traversal";
        cout<<"\n5.Inorder Traversal";
        cout<<"\n6.Postorder Traversal";
        cout<<"\n7.Swap left and right pointers";
        cout<<"\n8.Height of tree";
        cout<<"\n9.Copy Tree";
        cout<<"\n10.Number of leaves";
        cout<<"\n11.Number of Internal Nodes";
        cout<<"\n12.Erase all nodes";
        cout<<"\n\nEnter your choice : ";
        cout<<"\n>>>";
        cin>>choice;
        switch(choice)
        {
            case 1:
                cout<<"\nRecursive Preorder Traversal : ";
                obj.preorder_rec(obj.root);
                break;
            case 2:
                cout<<"\nRecursive Inorder Traversal : ";
                obj.inorder_rec(obj.root);
                break; 
            case 3:
                cout<<"\nRecursive Postorder Traversal : ";
                obj.postorder_rec(obj.root);
                break; 
            case 4:
                cout<<"\nPreorder Traversal : ";
                obj.preorder();
                break;
            case 5:
                cout<<"\nInorder Traversal : ";
                obj.inorder();
                break; 
            case 6:
                cout<<"\nPostorder Traversal : ";
                obj.postorder();
                break;
            case 7:
                obj.root=obj.swap(obj.root);
                cout<<"\nSwapped...";
                break;
            case 8:
                int h;
                h=obj.height(obj.root);
                cout<<"\nHeight of tree : "<<h;
                break;
            case 9:
                obj2.root=obj.copy(obj.root);
                break;                  
            case 10:
                int ln;
                ln=obj.count_leaf(obj.root);
                cout<<"\nNumber of leaf nodes : "<<ln;
                break; 
            case 11:
                int in;
                in=obj.count_internal(obj.root);
                cout<<"\nNumber of internal nodes : "<<in;
                break;
            case 12:
                obj.root=obj.makeempty(obj.root);
                break;                                                               
        }
    }
}
