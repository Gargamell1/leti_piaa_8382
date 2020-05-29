#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <map>
#include <set>
using namespace std;	

int main()
{
	string p;
	int i,j,fl=0;
	vector <int> pp;//Prefix-function for P
	vector <int> ans;//Vector for answers
	getline(cin,p);//Input line P
	pp.push_back(0);
	i=1;
	j=0;
	while(p[i]!='\0')//start deploying values into Prefix-function
	{
		if(p[i]==p[j])
		{
			pp.push_back(j+1);

			j++;
			i++;
		}
		else
		{
			if(j==0)
			{
				pp.push_back(0);
				i++;
			}
			else
			{
				j=pp[j-1];
			}
		}
	}

	i=0;
	j=0;
	char x=getchar();
	while(x!='\n')//Starting go on T , to find entry
	{
		if(p[j]==x)
		{
			if(pp.size()-1==j)//if whole string P was found in T
			{
				ans.push_back(i-j);
			    fl=1;
				if(j!=0)//To not (Seg fault)
				j=pp[j-1];
				else
				{
				i++;
						x=getchar();	
				}
			}
			else
			{
			x=getchar();		
			i++;
			if(p[j+1]!='\0')
				j++;
			}
		}
		else
		{
			if(j!=0)
			{
				j=pp[j-1];//Back to nearest entry
			}
			else
			{
				i++;//Stepin
				x=getchar();		
			}
		}
		
	}
	if(fl==0)
	{
		cout<<"-1";
		return 0;
	}
	cout<<ans[0];
	for(int u=1;u<ans.size();u++)
	{
		cout<<","<<ans[u];
	}
	cout<<endl;
	//cout<<"  String P = "<<p<<endl;
//	cout<<"  String T = "<<t<<endl;
system("pause");
	return 0;
}
