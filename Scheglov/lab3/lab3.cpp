#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <map>
#include <set>

using namespace std;

struct Pair{//Struct of edges
	char u;
	char v;
	double co;
	double ci;
	int pot;
	Pair(char a,char b,double x,double y)
	{
		u=a;
		v=b;
		co=x;
		ci=y;
		pot=0;
	}
	/*Pair(Pair &pair)
	{
		u=pair.u;
		v=pair.v;
		ci=pair.ci;
		co=pair.co;					
	}*/
};

struct Node {//Struct of vertex
    char name;
    char prev;
    vector<Pair> E;
    int flag;
    
    Node(char c) 
	{
        name = c;
        flag=0;
    }
    
};



int main()
{
	int n, fl=0,im,im1,skip=0,uuu=0;
	char a, b,s,e, x;
    double c;
    vector<Node> Nodes;
    vector<Pair> P2;
    vector<Pair> P21;    
    Pair P3(a,b,0,0);
    Pair P22(a,b,0,0);
    Pair P23(a,b,0,0);
    double max=0,sum=0,cm=-1;
    cin>>n;
    cin>>a;
    cin>>b;

    if(a==b)
    {
    	cout<<"0"<<endl;//Special occasion

    for(int i=0;i<n;i++)
    {
    	cin>>a>>b>>c;
    	cout<<a<<" "<<b<<" 0"<<endl;

    }    	return 0;}
    Node ch=Node('0');
    Node chd=Node('0');    
    Pair ch2=Pair(a,b,0,0);
    s=a;
    e=b;
    Nodes.push_back(Node(a));
    Nodes.push_back(Node(b));    
    for(int i=0;i<n;i++)
    {
    	cin>>a>>b>>c;//Input edges
    	P22.u=a;
    	P22.v=b;
    	P22.co=c;
    	P2.push_back(P22);
    	for(int j=0;j<Nodes.size();j++)
    	{
    		if(Nodes[j].name==a)
    		{
				fl=1;
				im=j;
			}
		}
		if(fl==0)
		{
			ch=Node(a);	
			ch.E.push_back(Pair(a,b,c,0));//adding edges and vertex
			Nodes.push_back(ch);
		}
		else
		{
			ch=Nodes[im];
			for(int k=0;k<ch.E.size();k++)
			{
				ch2=ch.E[k];
				if(ch2.u==a&&ch2.v==b)
				{
					skip =1;
					im1=k;
				}
			}
			if(skip==1)
			{
				ch2=ch.E[im1];
				ch2.ci+=0;
				ch2.co+=c;
				ch.E.erase(ch.E.begin()+im1);
				ch.E.push_back(ch2);
			}
			else
			{
			ch.E.push_back(Pair(a,b,c,0));
			}
			Nodes.erase(Nodes.begin()+im);
			Nodes.push_back(ch);			
		}
		fl=0;
		skip=0;
		for(int j=0;j<Nodes.size();j++)
    	{
    		if(Nodes[j].name==b)
    		{
				fl=1;
				im=j;
			}
		}
		if(fl==0)
		{
			ch=Node(b);	
			ch.E.push_back(Pair(b,a,0,c));//adding edges and vertex
			Nodes.push_back(ch);
		}
		else
		{
			ch=Nodes[im];
			for(int k=0;k<ch.E.size();k++)
			{
				ch2=ch.E[k];
				if(ch2.u==b&&ch2.v==a)
				{
					skip =1;
					im1=k;
				}
			}
			if(skip==1)
			{
				ch2=ch.E[im1];
				ch2.ci+=c;
				ch2.co+=0;
				ch.E.erase(ch.E.begin()+im1);
				ch.E.push_back(ch2);
			}
			else
			{
			ch.E.push_back(Pair(b,a,0,c));
			}
			Nodes.erase(Nodes.begin()+im);
			Nodes.push_back(ch);
			skip=0;			
		}
		fl=0;
	}
cout<<endl<<"For = "<<x<<endl;
	for(int i=0;i<Nodes.size();i++)
	{
		ch=Nodes[i];
		cout<<"Versh = "<<ch.name<<" Flag = "<<ch.flag<<endl;
		for(int j=0;j<ch.E.size();j++)
		{
			ch2=ch.E[j];
			cout<<"vec ("<<ch2.u<<":"<<ch2.v<<") = "<<ch2.co<<"/"<<ch2.ci<<endl;
		}
		cout<<endl<<endl;
	}//thats what we get the vertexes with their edges
	
while(1)
{

	x=s;//Starting from the start
	im=0;
	for(int l=0;l<Nodes.size();l++)
		{
			ch=Nodes[l];
			if(s==ch.name)
			{
				im=l;
			}
		}			
	ch=Nodes[im];
//	cout<<"Nachinaem s "<<ch.name<<endl;
	ch.prev='0';
	while(x!=e)//if not in the end
	{
		for(int j=0;j<ch.E.size();j++)
		{
			ch2=ch.E[j];
			for(int l=0;l<Nodes.size();l++)
			{
				chd=Nodes[l];
				if(ch2.v==chd.name&&chd.flag==1)
				{
					skip=1;//we cant go in this vertex
				}
			}
			if(skip!=1)
			{
				if(ch2.co>0)//compare the values
				{
					if(max==0)
					{
						max=ch2.co;
						P3=ch2;
					}
					else
					{
						if(max<ch2.co)
						{
							max=ch2.co;
							P3=ch2;					
						}
					}
				}
			}
			skip=0;			
		}
		max=0;
		cout<<" rebro vibrano ("<<P3.u<<"."<<P3.v<<") ves = "<<P3.co<<endl;
		if(P3.co==-1)//output the answer
		{
			ch.flag=1;
			Nodes.erase(Nodes.begin()+im);
			Nodes.push_back(ch);
			x=ch.prev;
			if(x=='0')
			{
			/*		cout<<endl<<"For = "<<x<<endl;
	for(int i=0;i<Nodes.size();i++)
	{
		ch=Nodes[i];
	cout<<"Versh = "<<ch.name<<" Flag = "<<ch.flag<<endl;
		for(int j=0;j<ch.E.size();j++)
		{
			ch2=ch.E[j];
			cout<<"vec ("<<ch2.u<<":"<<ch2.v<<") = "<<ch2.co<<"/"<<ch2.ci<<endl;
		}
		cout<<endl<<endl;
	}*/	
				cout<<sum<<endl;	
			for(int p =0;p<P2.size();p++)
			{	
				P22=P2[p];
				for(int i=0;i<Nodes.size();i++)
				{
					ch=Nodes[i];
					for(int j=0;j<ch.E.size();j++)
					{
						ch2=ch.E[j];
						if(ch2.u==P22.u&&ch2.v==P22.v)
						{
                                if(ch2.pot==0)
                                {
                                	cout<<ch2.u<<" "<<ch2.v<<" 0"<<endl;
                                }
                                else
							cout<<ch2.u<<" "<<ch2.v<<" "<<ch2.pot<<endl;
						}
					}
				}
			}
			
				return 0;
			}
			for(int l=0;l<Nodes.size();l++)
			{
				ch=Nodes[l];
				if(x==ch.name)
				{
					im=l;
				}
			}
			ch=Nodes[im];
			continue;
		}			
//max flow in this path
		if(cm==-1)
			cm=P3.co;
		if(cm>P3.co)
			cm=P3.co;
		ch.flag=1;
		Nodes.erase(Nodes.begin()+im);
		Nodes.push_back(ch);						
		for(int l=0;l<Nodes.size();l++)
		{
			ch=Nodes[l];
			if(P3.v==ch.name)
			{
				im=l;
			}
		}			
		ch=Nodes[im];
	//	cout<<"Teper v "<<ch.name<<endl;		
		ch.prev=P3.u;
		x=ch.name;
		P3.co=-1;
	}
	sum+=cm;
	im1=im;
	x=e;
	while(x!=s)//From the end to the start and change the values of bandwidth

	{
		for(int j=0;j<ch.E.size();j++)
		{
			ch2=ch.E[j];
			if(ch2.v==ch.prev)
			{
				im=j;
			}
		}
		ch2=ch.E[im];
		ch2.ci-=cm;//change value of bandwidth
		ch2.co+=cm;//change value of bandwidth
		if(ch2.pot-cm>=0)
			ch2.pot+=cm;//true flow		
		ch.E.erase(ch.E.begin()+im);
		ch.E.push_back(ch2);
		ch.flag=0;		
		Nodes.erase(Nodes.begin()+im1);
		Nodes.push_back(ch);
		//Changing for the last vertex almost complete
		a=ch.prev;		
		b=ch.name;
		for(int l=0;l<Nodes.size();l++)
		{
			ch=Nodes[l];
			if(a==ch.name)
			{
				im1=l;
			}
		}				
		ch=Nodes[im1];
		for(int j=0;j<ch.E.size();j++)
		{
			ch2=ch.E[j];
			if(ch2.v==b)
			{
				im=j;
			}
		}
		
		ch2=ch.E[im];
		ch2.ci+=cm;//change value of bandwidth
		ch2.co-=cm;//change value of bandwidth
		ch2.pot+=cm;//true flow
		ch.E.erase(ch.E.begin()+im);
		ch.E.push_back(ch2);
		ch.flag=0;
		Nodes.erase(Nodes.begin()+im1);
		Nodes.push_back(ch);
		b=ch.prev;
		x=ch.name;	
		//changing for the prev to last complete for half and for the last is complete
		for(int l=0;l<Nodes.size();l++)
		{
			chd=Nodes[l];
			if(x==chd.name)
			{
				im1=l;
			}
		}
		ch=Nodes[im1];//next vertex to handle

	//	cout<<" PREV else = "<<b<<endl;		
	//	cout<<" PREV = "<<ch.prev<<endl;
	//	cout<<" at the same moment = "<<ch.name<<endl;		
	//	cout<<" now = "<<x<<endl;
	}

//	cout<<" func = "<<cm<<endl;
}


	return 0;
}
