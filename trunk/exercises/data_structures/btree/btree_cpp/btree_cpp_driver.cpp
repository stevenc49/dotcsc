#include <iostream>
#include "btree_cpp.h"

using namespace std;

int main()
{
    Btree tree; // = new Btree();
    int i;

    for(i=0; i<=100; i++)
    {
        tree.insert(i);
    }

    tree.destroy_tree();

    if ( tree.search(15) != NULL )
        cout << "found\n" << endl;
    else
        cout << "not found\n" << endl;



    return 0;
}
