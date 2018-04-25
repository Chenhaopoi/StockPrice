#include <stdio.h>
#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;
int t;
char style;
double ri,r,u,d,X;
double s[100][100],v[100][100]; /* array s means stock price, array v is value of option, 
                                  actually in this model, if we want to save time and space of RAM, 
								  we even don't need 's' */
void input()
{
	cout<<"Please enter the initial stock price S0=";
	cin>>s[0][0];
	cout<<"Up factor U=";
	cin>>u;
	cout<<"Down factor D=";
	cin>>d;
	cout<<"Exerise price X=";
	cin>>X;
	cout<<"Time maturity T=";
	cin>>t;
	cout<<"Interest rate R=";
	cin>>ri;
	r=exp(ri);
}                              /* input data via keyboard*/  
void btree()
{
    for (int i=1;i<=t;++i)
    {
    	s[i][0]=s[i-1][0]*d;
		for (int j=1;j<=i;j++)
    	{
    		s[i][j]=s[i][j-1]/d*u;
		}
	} 
	
	/* compute stock price
	  for (int i=1;i<=t;++i)  s[i][0]=s[i-1][0]*d;
	  for (int j=1;j<=t;j++)  s[t][j]=s[t][j-1]/d*u;
	 */
	
} 
double callo()
{ 
	double p=(r-d)/(u-d);  
	for (int i=0;i<=t;++i)
	{
		if (s[t][i]>X) v[t][i]=s[t][i]-X; else v[t][i]=0;
	}
	for (int i=t-1;i>=0;i--)
	{
		for (int j=0;j<=i;j++)
		{
			v[i][j]=((1-p)*v[i+1][j]+p*v[i+1][j+1])/r;
		}
	}
	return v[0][0];
}  /* compute option price
     call option. 
     */
double puto()
{ 
	double p=(r-d)/(u-d);  
	for (int i=0;i<=t;++i)
	{
		if (s[t][i]<X) v[t][i]=X-s[t][i]; else v[t][i]=0;
	}
	for (int i=t-1;i>=0;i--)
	{
		for (int j=0;j<=i;j++)
		{
			v[i][j]=((1-p)*v[i+1][j]+p*v[i+1][j+1])/r;
		}
	}
	return v[0][0];
	/* compute option price
	 put option.
	*/
} 
void outputtree()
{
	cout<<endl;
	for (int i=0;i<=t;i++)
	cout<<"   V"<<i<<"   ";
	cout<<endl;
	for (int j=0;j<=t;j++)
	{
		for (int k=0;k<j;k++)
		cout<<setw(8)<<left<<' ';
		for (int i=j;i<=t;i++)
		cout<<fixed<<setprecision(2)<<setw(8)<<right<<v[i][i-j];
		cout<<endl;
		
	}
	cout<<endl<<endl;
}

int main()
{
	do
	{
		cout<<"Please input the type of option:\n1.European call option\n2.European put option"<<endl<<"or other key to exit\n";
		cin>>style;
		if (not((style=='1')or(style=='2'))) {	cout<<"invaild input!"; exit(0); }
		input();
	    if (style=='1') { btree(); cout<<endl<<"The option price is "<<fixed<<setprecision(2)<<callo()<<endl; outputtree();} else 
		{
	        if (style=='2') { btree(); cout<<endl<<"The option price is "<<fixed<<setprecision(2)<<puto()<<endl; outputtree(); }
		}
    }
    while (((style=='1')or(style=='2')));
	return 0;	 
} /*main program. this code was written by Poi. */

