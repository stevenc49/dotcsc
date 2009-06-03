#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
int num[10]; // massive of integers
int count=10; // number of ints to output
cout << "input not more than 10 \n";
cout << "numbers value '42' = stop\n";
for (int n=0; n<10; n++)
{
cout << endl << n+1 << ". ";
cin >> num[n];
if (num[n]==42) {count=n; n=12;
cout << "\nStop command detected! \n";
cout << "Numbers to output = " << count << endl; }
}

cout << endl << endl << "Your output\n";
for (int a=0; a<count; a++)
{
cout << num[a] << endl;
}

return 0;
} 