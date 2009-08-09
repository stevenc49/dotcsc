
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>

using namespace std;

template <class T>
inline void PRINT_ELEMENTS (const T& coll)
{
    typename T::const_iterator pos;

    //std::cout << optcstr;
    for (pos=coll.begin(); pos!=coll.end(); ++pos) {
        std::cout << *pos << endl;
    }
    std::cout << std::endl;
}

void initializeList(list<int> &list, int start, int end)
{
    //hack because 1 is not a prime number
    if (start==1)
        start = 2;

    for(int i=start; i<=end; i++)
        list.push_back(i);
}

void removeMultiplesOfNum(int num, list<int> &lst)
{
    list<int>::iterator itr;

    for(itr = lst.begin(); itr != lst.end(); )
    {
        if ( *itr % num == 0 && *itr != num )
        {
            itr=lst.erase(itr);
        }
        else
          ++itr;
    }
}

int getFirstNumGreaterThanPrime(int prime, list<int> &lst)
{
    list<int>::iterator itr;

    for(itr = lst.begin(); itr != lst.end(); itr++)
    {
        if( *itr > prime )
        {
            return *itr;
        }
    }
}

list<int> sieve(int num)
{
    int prime = 2;

    list<int> lst;

    initializeList(lst, 2, num);

    do
    {
        removeMultiplesOfNum(prime, lst);
        prime = getFirstNumGreaterThanPrime(prime, lst);
    } while ( pow(float(prime),2)<num );

    return lst;
}

list<int> modifiedSieve(list<int> &precomputed, list<int> &range)
{
    list<int>::iterator preItr;

    for(preItr = precomputed.begin(); preItr != precomputed.end() ; preItr++)
    {
        removeMultiplesOfNum(*preItr, range);
    }

    return range;
}

list<int> testCase(int start, int end)
{
    int maxPrime = sqrt(end);
    list<int> precomputed = sieve(maxPrime);

    list<int> range;
    initializeList(range, start, end);

    range = modifiedSieve(precomputed, range);

    return range;
}

class TestCase
{
public:
    TestCase()
    {
    }

    void setRange()
    {
        string rangeInput = "";
        getline(cin, rangeInput);

        stringstream lineStream(rangeInput);

        int i;
        vector<int> bounds;

        while (lineStream >> i)
            bounds.push_back(i);

        lower_bound = bounds[0];
        upper_bound = bounds[1];
    }

    void compute()
    {
        int maxPrime = sqrt(upper_bound);
        list<int> precomputed = sieve(maxPrime);

        initializeList(primes, lower_bound, upper_bound);

        primes = modifiedSieve(precomputed, primes);
    }

    void print()
    {
        PRINT_ELEMENTS(primes);
    }

private:
    int lower_bound;
    int upper_bound;
    list<int> primes;
};

class TestCaseContainer
{
public:
    TestCaseContainer()
    {
    }

private:
    vector<TestCase> container;
};

int main()
{
    int numTestCase;
    cin>>numTestCase;

    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    vector<TestCase> v_testCases;

    for(int i=0; i<numTestCase; i++)
    {
        v_testCases.push_back( TestCase() );
    }

    for(int i=0; i<numTestCase; i++)
    {
        v_testCases[i].setRange();
        v_testCases[i].compute();
    }

    for(int i=0; i<numTestCase; i++)
    {
        v_testCases[i].print();
    }

//    vector<TestCase>::iterator itr;
//    for(itr = v_testCases.begin(); itr != v_testCases.end(); itr++)
//    {
//        string input = "";
//        getline(cin, input);
//        itr->setRange(input);
//    }
}
