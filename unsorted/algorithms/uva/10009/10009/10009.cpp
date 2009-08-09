#include <boost/thread/thread.hpp>
#include <iostream>
#include "windows.h"

using namespace std;
using namespace boost;

void even()
{
	for(int i=0; i<=100; i+=2)
	{
		cout << i << endl;
		Sleep(1000);
	}
}

void odd()
{
	for(int i=1; i<=99; i+=2)
	{
		cout << i << endl;
		Sleep(1000);
	}
}

int main(int argc, char* argv[])
{
	thread thrd1(&even);
	thread thrd2(&odd);

	thrd1.join();
	thrd2.join();

	return 0;
}
