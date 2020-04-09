#include <iostream>
using namespace std;
char e[100];
int check(char a[],int n)
{
    int flag=1;
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(a[i]==a[j])
                flag=0;
        }
    }
    return flag;
}//hmmm
void Try(int i,string a)
{
    for(int j=0;j<a.length();j++)
    {
        e[i]=a[j];
        if(i==a.length()-1)
        {
            for(int k=0;k<a.length();k++)
                cout<<e[k];
            cout<<endl;

        }
        else
            Try(i+1,a);
    }
}
void split(string a,string s[],int &k)
{
    int kt=1,i=0;
    k=0;
    while(1)
    {
        s[k]=a.substr(i,kt);
        k++;
        if(kt+i<a.length())
            i++;
        else
        {
            kt++;
            i=0;
            if(kt>a.length())
                break;
        }
    }
}
int main()
{
    string a,s[100];
    cin>>a;
    int n;
    split(a,s,n);
    for(int i=0;i<n;i++)
        Try(0,s[i]);


}
