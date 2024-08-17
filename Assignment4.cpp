#include <iostream>
#include<iomanip>
using namespace std;

class Hash
{
	long long int *table_wor;
	long long int *table_wr;

	public:
	Hash()
	{
		table_wor=new long long int[10];
		table_wr=new long long int[10];
		for(int i=0;i<10;i++)
		{
			table_wr[i]=0;
			table_wor[i]=0;
		}
	}

	void lp_WithoutReplacement(long long int x)
	{
		int key=x%10;
		if(table_wor[key]==0)
		{
			table_wor[key]=x;
		}
		else
		{
			int i=key;
			while(table_wor[i]!=0)
			{
				if(i==9)
				{
					i=0;
				}
				else
				{
					i++;
				}
				if(i==key)
				{
					cout<<"\nHash Table is Full";
					return;
				}
			}
			table_wor[i]=x;
		}
	}
	
	void lp_WithReplacement(long long int x)
	{
		int key=x%10;
		if(table_wr[key]==0)
		{
			table_wr[key]=x;
		}
		else if(table_wr[key]!=0)
		{
			long long int temp;
			if(table_wr[key]%10!=key)
			{
				temp=table_wr[key];
				table_wr[key]=x;
				int i=key;
				while(table_wr[i]!=0)
				{
					if(i==9)
					{
						i=0;
					}
					else
					{
						i++;
					}
					if(i==key)
					{
						cout<<"\nHash Table is Full";
						return;
					}
				}
				table_wr[i]=temp;
			}
			else
			{
				int i=key;
				while(table_wr[i]!=0)
				{
					if(i==9)
					{
						i=0;
					}
					else
					{
						i++;
					}
					if(i==key)
					{
						cout<<"\nHash Table is Full";
						return;
					}
				}
				table_wr[i]=x;
			}
		}
	}


	int comparison_wor(long long int x)
	{
		int key=x%10;
		if(table_wor[key]==x)
		{
			return 1;
		}
		else
		{
			int c=1;
			int i=key;
			while(table_wor[i]!=x)
			{
				if(i==9)
				{
					i=0;
				}
				else
				{
					i++;
				}
				c++;
			}
			return c;
		}
	}

	int comparison_wr(long long int x)
	{
		int key=x%10;
		if(table_wr[key]==x)
		{
			return 1;
		}
		else
		{
			int c=1;
			int i=key;
			while(table_wr[i]!=x)
			{
				if(i==9)
				{
					i=0;
				}
				else
				{
					i++;
				}
				c++;
			}
			return c;
		}
	}

	void show()
	{
		cout<<"\nLinear Probing without Replacement"<<setw(40)<<"Linear Probing with Replacement";
		for(int i=0;i<10;i++)
		{
			cout<<"\n"<<i<<" : "<<table_wor[i]<<setw(30)<<i<<" : "<<table_wr[i];
		}
	}
};



int main()
{
	Hash h;
	long long int x;
	int choice;
	while(1)
	{
		cout<<"\n*********** MENU *************";
		cout<<"\n1.Insert without Replacement";
		cout<<"\n2.Show";
		cout<<"\n3.Comparisons";
		cout<<"\nEnter choice : ";
		cin>>choice;
		switch(choice)
		{
		case 1:
			cout<<"\nEnter mobile number : ";
			cin>>x;
			h.lp_WithoutReplacement(x);
			h.lp_WithReplacement(x);
			break;
		case 2:
			h.show();
			break;
		case 3:
			cout<<"\nEnter mobile number to find comaprison : ";
			cin>>x;
			cout<<"\nComparisons without replacement : "<<h.comparison_wor(x);
			cout<<"\nComparisons with replacement : "<<h.comparison_wr(x);
		}
	}
	return 0;

}
