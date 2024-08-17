#include<iostream>
#define MAX 10
using namespace std;

class Node
{
	public:
		int data;
		Node* left;
		Node* right;
		
		Node(int d)
		{
			data=d;
			left=right=NULL;
		}
		
		Node()
		{
			data=0;
			left=right=NULL;
		}
};

class OBST
{
	public:
		Node* root;
		
		OBST()
		{
			root=NULL;
		}
		
		Node* construct(int r[MAX][MAX],int i,int j)
		{
			if(r[i][j]==0)
			{
				return NULL;
			}
			else
			{
				int num=r[i][j];
				Node* p=new Node(num);
				p->left=construct(r,i,num-1);
				p->right=construct(r,num,j);
				return p;
			}	
		}		
		
		Node* optimal(float p[],float q[],int n)
		{
			//cout<<"\nIn function";
			float w[n+1][n+1];
			float c[n+1][n+1];
			int r[MAX][MAX];
			int arr_k[n];
			float sum_k[n];
			int num=n;
			for(int i=0;i<=n;i++)
			{
				for(int j=0;j<=n;j++)
				{
					w[i][j]=c[i][j]=r[i][j]=0;
				}
			}
			//cout<<"\nAfter loop1";
			for(int i=0;i<=n;i++)
			{
				w[i][i]=q[i];
				c[i][i]=r[i][i]=0;
				//cout<<"\n\nw["<<i<<"]["<<i<<"]"<<w[i][i]<<"  c["<<i<<"]["<<i<<"]"<<c[i][i]<<"  r["<<i<<"]["<<i<<"]"<<r[i][i];
			}
			//cout<<"\nAfter loop2";
			int step;
			float sum=0;
			int i,j,k;
			for(step=1;step<=n;step++)
			{
				//cout<<"\nIn i loop i = "<<i;
				i=0;
				for(j=step;j<=n;j++)
				{
					//cout<<"\nIn j loop j = "<<j;
					sum=0;
					for(k=i+1;k<=j;k++)
					{
						//cout<<"\nq p = "<<q[k]<<" "<<p[k];
						sum=sum+q[k]+p[k];
					}
					//cout<<"\nsum = "<<sum;
					w[i][j]=q[i]+sum;
					
					int t;
					for(t=0;t<=n;t++)
					{
						arr_k[t]=0;
						sum_k[t]=99.9;						
					}
					t=0;
					for(k=i+1;k<=j;k++)
					{
						//cout<<"\nk = "<<k;
						arr_k[t]=k;
						sum_k[t]=c[i][k-1]+c[k][j];
						t++;
					}
					/*cout<<"\nsum_k :";
					for(int l=0;l<n;l++)
					{
						cout<<sum_k[l]<<" ";
					}
					cout<<"\narr_k :";
					for(int l=0;l<n;l++)
					{
						cout<<arr_k[l]<<" ";
					}*/
					int min=find_min(sum_k,n);
					//cout<<"\nmin k = "<<arr_k[min]<<"\nmin sum = "<<sum_k[min];
					c[i][j]=w[i][j]+sum_k[min];
					r[i][j]=arr_k[min];
					//cout<<"\n\nw["<<i<<"]["<<j<<"]"<<w[i][j]<<"  c["<<i<<"]["<<j<<"]"<<c[i][j]<<"  r["<<i<<"]["<<j<<"]"<<r[i][j];
					i++;
				}
			}
			root=this->construct(r,0,n);
			return root;
		}
		
		int find_min(float sum_k[],int n)
		{
			int min_idx=0;
			//cout<<"\narr : ";
			for(int i=0;i<=n;i++)
			{
				//cout<<sum_k[i]<<" ";
				if(sum_k[i]<sum_k[min_idx])
				{
					min_idx=i;
				}
			}
			return min_idx;
		}
					
		void Inorder(Node* T,char words[20][20])
		{
		    if(T==NULL)
		    {
		        return;
		    }
		    Inorder(T->left,words);
		    cout<<words[T->data-1]<<" -> ";
		    Inorder(T->right,words);
		}
};

int main()
{
	int n;
	cout<<"\nEnter the number of words : ";
	cin>>n;
	char words[n][20];
	float *p=new float[n];
	float *q=new float[n+1];
	cin.ignore();
	cout<<"\nEnter the words : ";
	for(int i=1;i<=n;i++)
	{
		cin.getline(words[i],20);
	}
	cout<<"\nEnter probabilities of successful search : ";
	for(int i=1;i<=n;i++)
	{
		cin>>p[i];
	}
	cout<<"\nEnter probabilities of unsuccessful search : ";
	for(int i=0;i<=n;i++)
	{
		cin>>q[i];
	}
	OBST o1;
	o1.root=o1.optimal(p,q,n);	
	o1.Inorder(o1.root,words);
	return 0;
}

