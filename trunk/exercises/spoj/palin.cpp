#include<iostream>
int palindrome(int );
using namespace std;
int main()
{
int no_of_palindromes;
cin>>no_of_palindromes;
int *pal_no=new int[no_of_palindromes];
for(int i=0;i<no_of_palindromes;i++)
{
cin>>pal_no[i];

}
for(int i=0;i<no_of_palindromes;i++)
cout<<palindrome(pal_no[i])<<endl;
return 0;
}

int palindrome(int n)
{
int k,sum;
for(int i=1;;i++)
{
k=n+i;sum=0;
while(k>0)
{
int c;
c=k%10;
k=k/10;
sum=sum*10+c;
}
if(sum==n+i)
return n+i;
}
}

