#include<iostream>

using namespace std;
void downward_adjustment(int* heap,int x)
{
    int n=heap[0];
    int i=x;
    while(2*i<=n)
    {
        int j=2*i;
        if(j+1<=n)
        {
            if(heap[j]<heap[j+1])
            {
                j=j+1;
            }
            
        }
        if(heap[i]<heap[j])
        {
            int temp=heap[i];
            heap[i]=heap[j];
            heap[j]=temp;
            i=j;
        }
        else
        {
            break;
        }
        
    }
}

int main()
{
	int MAX;
	cout<<"\nEnter the number of elements you want to create in tree : ";
	cin>>MAX;
    
	int *heap;
    heap=new int[MAX+1];
    
	heap[0]=MAX;
    for(int i=1;i<=MAX;i++)
    {
    	cout<<"\nEnter element of heap at position "<<i<<" : ";
        cin>>heap[i];  
    }
    
	cout<<"\nBefore : ";
    for(int i=1;i<=MAX;i++)
    {
        cout<<heap[i]<<" ";
    }
    
	for(int ind=MAX/2;ind>=1;ind--)
    {
        downward_adjustment(heap,ind);
    }
    
	cout<<"\nComplete Binary Tree : ";
    for(int i=1;i<=MAX;i++)
    {
        cout<<heap[i]<<" ";
    }    
    
	while(heap[0]>1)
    {
    	int last=heap[0];
    	int temp=heap[1];
    	heap[1]=heap[last];
    	heap[last]=temp;
    	heap[0]--;
    	downward_adjustment(heap,1);    	
	}
	heap[0]=MAX;
    cout<<"\nAfter sorting :\n";
    for(int i=1;i<=MAX;i++)
    {
        cout<<heap[i]<<" ";
    }    
}
