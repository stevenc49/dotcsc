
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

class MyClass
{
public:
    MyClass()
    {
    }

    void setXandY()
    {
        string rangeInput = "";
        getline(cin, rangeInput);

        stringstream lineStream(rangeInput);

        int i;
        vector<int> bounds;

        while (lineStream >> i)
            bounds.push_back(i);

        x = bounds[0];
        y = bounds[1];
    }

    int getX() const
    {
        return x;
    }

private:
    int x;
    int y;
};

int main()
{
    int someNum;
    cin>>someNum;
//
//cin.clear();
//cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


    MyClass c;
    c.setXandY();

    cout << c.getX() ;
}

