//primes of 2 to 100000 in 2.8 secs

#include <iostream>
#include <list>
#include <vector>
#include <math.h>

#define MIN 2
#define MAX 31622   //sqrt(100000) 31622

using namespace std;

int gcd(int a, int b);

int main()
{
    list<int> working_list;
    vector<int> prime_list;
    list<int>::iterator itr;
    int current_num;

    current_num = MIN;
    prime_list.push_back(MIN);   //2 is a prime too

    //create working list
    for(int i=MIN; i<=MAX; i++)
        working_list.push_back(i);

    while( current_num < MAX && !working_list.empty() )
    {
        for(itr = working_list.begin(); itr != working_list.end();)
        {
            //remove all multiples of the current num
            if ( *itr % current_num == 0 )
                itr=working_list.erase(itr);
            else
                ++itr;
        }

        //the first number in the list is a prime
        current_num = working_list.front();
        prime_list.push_back( current_num );
    }


    prime_list.pop_back(); //the last element is a dummy element

//    //print prime list
//    for(int i=0; i<prime_list.size(); i++)
//        cout<< i << ": " << prime_list[i] << endl;

    int lower= 2 ;
    int upper= 10  ;

    //for query range
    for(int i=lower; i<upper; i++)
    {
        //check all primes in precomputed list
        for(int j=1; j<prime_list.size(); j++)
        {
            //if composite number (not a prime)
            if( gcd(i,prime_list[j])!=1 )
                cout << i << endl;
        }
    }
}

int gcd(int a, int b)
{
  int c = a % b;
  while(c != 0)
  {
    a = b;
    b = c;
    c = a % b;
  }
  return b;
}

