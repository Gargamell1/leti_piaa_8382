#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

int MiniS(int n, int z)//‘ункци€ дл€ получени€ минимального возможного числа разбиений из позиции z
{
	int sum=0, i;
	for(i=n;i>0;i--)
	{
		sum+=z/(i*i);
		z=z%(i*i);
	}
	return sum;
}

int IsPlaceForP(int i,int j,int n,int p,int flag, int *s)//≈сть ли место дл€ размещени€ квадрата
{

	int a,b,v=0;
	if(flag==0)
	{
		for(a=0;a<p;a++)
		{
			for(b=0;b<p;b++)
			{
				v+=IsPlaceForP(a,b,n,p,1,s);
			}
		}		
	
	}
	else
	{
		if(i+n>p||j+n>p)
			return 0;
		for(a=i;a<i+n;a++)
		{
			for(b=j;b<j+n;b++)
			{
				if(s[a*p+b]!=0)
				{
					return 0;
				}
			}
		}
	}
	if(flag==1)
		return 1;
	if(v==0)
		return 0;
	else	
		return 1;	
}

int PlaceP(int i, int j, int n,int p, int *s)//–азместить квадрат
{
	int a,b;
	for(a=i;a<i+n;a++)
	{
		for(b=j;b<j+n;b++)
		{
			s[a*p+b]=n;
		}
	}	
	return i*p+j;
}
int DelP(int h,int p, int *s) //”далить квадрат
{
	int i=h/p,j=h%p, n=s[h],a,b;
	for(a=i;a<i+n;a++)
	{
		for(b=j;b<j+n;b++)
		{
			s[a*p+b]=0;
		}
	}	
	return 1;
}
int GetSimple(int N) //ѕолучить наименьшее простое число
{
	int i=2;
	while(1)
	{
	if(N%i==0)
		return i;
		i++;	
	}
}

int main()
{
    int N,i,j,a=0,b=0,place=0, maxplace,pz,min=1000;
    cin>>N;
    int p=GetSimple(N);
    int c=p,n=p/2,z[p*p],cz=-1;
    if(p==2) //ќбработка четных
    {
    	cout<<4<<endl;
		cout<<1<<" "<<1<<" "<<N/2<<endl;
		cout<<N/2+1<<" "<<1<<" "<<N/2<<endl;
		cout<<1<<" "<<N/2+1<<" "<<N/2<<endl;
		cout<<N/2+1<<" "<<N/2+1<<" "<<N/2;
    	return 0;
	}
    int s[p][p]={0};
    int square[p/2+1][p/2+1]={0};
    int answer[p/2+1][p/2+1]={0};
 	z[0]=0;
    for(i=0;i<p/2+1;i++)//—оздание и заполнение недоквадрата
    {
    	for(j=0;j<p/2+1;j++)
    	{
    		square[i][j]=0;
		}
	}	
	square[0][0]=-1;	
	if(p%2==0)
	{
  		PlaceP(0,0,p/2,p,&s[0][0]);
  		PlaceP(0,p/2,p/2,p,&s[0][0]);
  		PlaceP(p/2,0,p/2,p,&s[0][0]);		
  	}
	else
	{
		PlaceP(0,0,p/2+1,p,&s[0][0]);
		PlaceP(p/2+1,0,p/2,p,&s[0][0]);	
		PlaceP(0,p/2+1,p/2,p,&s[0][0]);
	}
	p=p/2+1;
	maxplace=p*p-1;

	i=0;
	j=0;
	while(square[z[0]/p][z[0]%p]!=1)
	{
		while(n>=1)
		{
			if(IsPlaceForP(i,j,n,p,0,&square[0][0]))
			{
				while(i<p)
				{
					while(j<p)
					{
						if(IsPlaceForP(i,j,n,p,1,&square[0][0]))
    					{
								cz++;//количество уже поставленных
    							pz=PlaceP(i,j,n,p,&square[0][0]);//ставим
    							place+=n*n;
    							z[cz]=pz;//заносим квадрат в массив
						}
						j++;
					}
					j=0;
					i++;
				}
			}
			i=0;
			j=0;
			n--;
		}
		if(cz<min)//¬ывод и хранение частичных решений
		{
			min=cz;
			cout<<min<<endl;
			for(i=0;i<p;i++)
    		{
    			for(j=0;j<p;j++)
    			{
    				answer[i][j]=square[i][j];
 					cout<<answer[i][j]<<" ";
				}
				cout<<endl;
			}	
		}
		for(i=0;i<p;i++)
		{
			for(j=0;j<p;j++)
			{
				
				if(square[i][j]==1)
				{
					cz--;
					DelP(i*p+j,p,&square[0][0]);
					place--;
				}
    				
			}
		}			
		n=square[z[cz]/p][z[cz]%p];
		DelP(z[cz],p,&square[0][0]);
		place-=n*n;			
		i=(z[cz]+1)/p;
		j=(z[cz]+1)%p;
		cz--;
		while(cz+MiniS(n,maxplace-place)>=min)
{
		n=square[z[cz]/p][z[cz]%p];
		DelP(z[cz],p,&square[0][0]);
		place-=n*n;			
		i=(z[cz]+1)/p;
		j=(z[cz]+1)%p;
		cz--;
}
		if(cz==-2)
			break;
	}
	p=GetSimple(N);//ѕреобразование ответа в положенный вид из записи матрицы
 	cout<<min+4<<endl;
	cout<<1<<" "<<1<<" "<<(p/2+1)*(N/p)<<endl;
	cout<<(p/2+1)*(N/p)+1<<" "<<1<<" "<<(p/2)*(N/p)<<endl;
	cout<<1<<" "<<(p/2+1)*(N/p)+1<<" "<<(p/2)*(N/p)<<endl; 	
	answer[0][0]=0;	
	
	j=1;
	for(i=0;i<p/2+1;i++)
    {
    	while(j<p/2+1)
    	{
    		if(answer[i][j]!=0)
    		{
			cout<<(p/2)*(N/p)+1+i*(N/p)<<" "<<(p/2)*(N/p)+1+j*(N/p)<<" "<<answer[i][j]*(N/p)<<endl;
    		DelP(i*(p/2+1)+j,p/2+1,&answer[0][0]);
    		}
    		j++;
		}
		j=0;
	}
    return 0;
}

