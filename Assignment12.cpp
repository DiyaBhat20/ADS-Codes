#include<iostream>
#include<fstream>
#include<string.h>
#define Max 10
using namespace std;


class hashing
{
    int roll[Max];
    int loc[Max];
    public:
    hashing()
    {
        for(int i=0;i<Max;i++)
        {
            roll[i]=-1;
            loc[i]=-1;
        }
    }

    int hashcode(int);
    void insert(int,int);
    void display();
    int search(int r);
    void deleteData(int r);
};

void hashing::deleteData(int r)
{
    int location=hashcode(r);
    int i=0;
    while(roll[location]!=-1)
    {
        if(roll[location]==r)
        {
            roll[location]=-1;
            loc[location]=-1;
            break;
        }
        i++;
        location=(location+1)%Max;
        if(i==Max)
        {
            cout<<"\nnot found";
            return;
        }
    }
}
int hashing::search(int r)
{
    int location=hashcode(r);
    if(roll[location]==r)
    {
        return loc[location];
    }
    else{

        int i=0;
        while(roll[location]!=r)
        {
            location=(location+1)%Max;
            i++;
            if(i==Max)
            {
                cout<<"\nnot found";
                return -1;
            }
        }
        return loc[location];
    }
}
int hashing::hashcode(int r)
{
    return r%10;
}
void hashing::display()
{
    for(int i=0;i<Max;i++)
    {
        if(roll[i]==-1)
        {
            cout<<"\nEMPTY";
        }
        else{
            cout<<"\nroll no:"<<roll[i]<<"   location:"<<loc[i];
        }
    }
}
void hashing::insert(int r,int l)
    {
        cout<<"\nloc:"<<l<<"    "<<"roll:"<<r<<endl;
        int location=hashcode(r);
        cout<<location<<endl;
        if(roll[location]==-1)
        {
            roll[location]=r;
            loc[location]=l;
            cout<<"\ndone";
            return;
        }
        else{
            int i=0;
            int tempr=roll[location];
            int templ=loc[location];
            int flag=0;
            if(hashcode(tempr)!=location)
            {
                roll[location]=r;
                loc[location]=l;
                flag=1;
            }
            while(roll[location]!=-1)
            {
                location=(location+1)%Max;
                i++;
                if(i==Max)
                {
                    cout<<"\nHash Table is Full";
                    return;
                }
            }
            if(flag==0)
            {
                 roll[location]=r;
                loc[location]=l;
            }
            else
            {
                roll[location]=tempr;
                loc[location]=templ;
            }
           
        }
}
class stdRecord;

class student
{
    
    int roll_no;
    char name[100];
    char div;
    char add[100];
    public:
    student()
    {
        roll_no=0;
        strcpy(name,"");
        div=' ';
        strcpy(add,"");
    }
    student(int r,char* n,char d,char* a)
    {
        roll_no=r;
        strcpy(name,n);
        div=d;
        strcpy(add,a);
    }

    friend ostream& operator <<(ostream& out,student s)
    {
        cout<<"\nname:"<<s.name;
        cout<<"\nroll no:"<<s.roll_no;
        cout<<"\ndiv:"<<s.div;
        cout<<"\nadd:"<<s.add;
        return cout;
    }

    friend istream& operator >>(istream& in,student& s)
    {
        in.ignore(1);
        cout<<"\nEnter name:";
        in.getline(s.name,100);

        cout<<"\nEnter roll no:";
        in>>s.roll_no;

        cout<<"\nEnter division:";
        in>>s.div;

        in.ignore(1);
        cout<<"\nEnter address:";
        in.getline(s.add,100);
        return in;
    }
   
   friend class stdRecord;
    
};

class stdRecord
{
    char path[100];
    public:
    stdRecord()
    {
        strcpy(path,"D:\\Sem4\\ADS Assignments\\student1.txt");
    }

    void addData(student s,hashing &h)
    {
        fstream fobj;
        fobj.open(path,ios::app | ios::binary);

        if(fobj.fail())
        {
            cout<<"\nfile not connected to add data";
            exit(0);
        }
        fobj.seekg(0,ios::end);
        cout<<"\nfile connected to add data";
        h.insert(s.roll_no,fobj.tellg());
        fobj.write((char*)&s,sizeof(s));
        fobj.close();
        
    }

    void display(hashing& h)
    {
        fstream fobj;
        fobj.open(path,ios::in| ios::binary);
        if(fobj.fail())
        {
            cout<<"\nFail to connect to display";
            exit(0);
        }

        cout<<"\nconnected to read";

        student s;
        while(fobj.read((char*)&s,sizeof(s)))
        {
            cout<<s;
            cout<<endl;
        }
        fobj.close();
        char ch;
        cout<<"\nyou want to display hash table y/n:";
        cin>>ch;
        if(ch=='y')
        {
            h.display();
        }
    }

    void search(int roll,hashing h)
    {
        fstream fobj;
        fobj.open(path,ios::in | ios::binary);
        if(fobj.fail())
        {
            cout<<"\nFail to connect to display";
            exit(0);
        }

        cout<<"\nconnected to search";
        student s;
        int loc=h.search(roll);
        if(loc!=-1)
        {
            fobj.seekg(loc,ios::beg);
            fobj.read((char*)&s,sizeof(s));
            cout<<s;
        }
        else
        {
            cout<<"\nnot found";
        }
        fobj.close();

    }

    void deleteStudent(int roll,hashing& h)
    {
        fstream fobj;
        fobj.open(path,ios::in | ios::binary);
        if(fobj.fail())
        {
            cout<<"\nFail to connect to display";
            exit(0);
        }

        cout<<"\nconnected to delete";

        fstream newobj;
        newobj.open("D:\\Sem4\\ADS Assignments\\temp1.txt",ios::app | ios::binary);
        student std;
        int loc=h.search(roll);
        if(loc==-1)
        {
            cout<<"\nnot found to delete";
            return;
        }
        int f=0;
        while(fobj.read((char*)&std,sizeof(std)))
        {
            
            if(std.roll_no!=roll){
                newobj.write((char*)&std,sizeof(std));
            }
            else{
                f=1;
            }
        }
        h.deleteData(roll);
        fobj.close();
        newobj.close();
        remove("D:\\Sem4\\ADS Assignments\\student1.txt");
        rename("D:\\Sem4\\ADS Assignments\\temp1.txt","D:\\Sem4\\ADS Assignments\\student1.txt");
    }
};

int main()
{
    student s;
    stdRecord rec;
    hashing h;
    int roll;
    while(1)
    {
        cout<<"\n----- MENU -----";
        cout<<"\n1-add\n2-display\n3-search\n4-delete\n5-exit";
        int choise;
        cout<<"\nEnter choise:";
        cin>>choise;
        switch (choise)
        {
            case 1:cin>>s;
                    rec.addData(s,h);
                    break;
            case 2:rec.display(h);
                    break;
            case 3:cout<<"\nEnter roll no to search:";
                    cin>>roll;
                    rec.search(roll,h);
                    break;
            case 4:cout<<"\nEnter roll no delete:";
                    cin>>roll;
                    rec.deleteStudent(roll,h);
                    break;
            case 5:cout<<"\n--- Exit ----";
                    exit(0);
        default:cout<<"\n";
                exit(0);
            break;
        }
    }
   
}
