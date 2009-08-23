
//4
//9 0123456789 oF8
//Foo oF8 0123456789
//13 0123456789abcdef 01
//CODE O!CDE? A?JM!.

#include <string>
#include <vector>
#include <iostream>
#include <istream>
#include <ostream>
#include <iterator>
#include <sstream>
#include <algorithm>
#include <strstream>

using namespace std;

template<class Source>
string ToString(const Source& Value)
{
    strstream ss;
    ss << Value << '\0';
    string os = ss.str();
    ss.freeze(false);
    return os;
}

class Language
{
public:
    Language()
    {
    }

    void setPrecedence(string str)
    {
        for(int i=0; i<str.length(); i++)
        {
            precedence.push_back(str[i]);
        }
    }

    char getNextChar(char c)
    {
        vector<char>::iterator it;

        it = find(precedence.begin(), precedence.end(), c);
        ++it;
        return *it;
    }

    char getFirstChar()
    {
        return precedence.front();
    }

    char getFirstNonZeroChar()
    {
        return precedence[1];
    }

    char getLastChar()
    {
        return precedence.back();
    }

private:
    vector<char> precedence;
};

class AlienNumber
{
public:
    AlienNumber()
    {
    }

    void increment()
    {
        increment_recursive(1);
    }

    void setNum(string num)
    {
        number = num;
    }

    string getNum() const
    {
        return number;
    }

    void setLanguage(Language lang)
    {
        language = lang;
    }

private:
    string number;
    Language language;

    void increment_recursive(unsigned int pos)
    {
        char digit = number[ number.size()-pos ];

        bool allLastChar = true;

        for(int i=0; i<number.length(); i++)
        {
            if(number[i]!=language.getLastChar())
            {
                allLastChar = false;
                break;
            }
        }

        if(allLastChar) //ex: lang: base 10, number: 999
        {
            for(int i=0; i<number.length(); i++)
            {
                number.replace( i, 1, ToString(language.getFirstChar() ) );
            }
            number.insert( 0, ToString(language.getFirstNonZeroChar()) );
        }
        else
        {
            if (digit != language.getLastChar())    //ex: lang: base 10, number: 128
            {
                char nextChar = language.getNextChar(digit);
                number.replace( number.size()-pos , 1, ToString(nextChar) );
            }
            else    //ex: lang: base 10, number: 129
            {
                number.replace( number.size()-pos , 1, ToString(language.getFirstChar()) );
                pos++;
                increment_recursive(pos);
            }
        }
    }
};

class TestCase
{
public:
    TestCase()
    {
    }

    void parseTestCase()
    {
        string input = "";
        getline(cin, input);

        stringstream strstr(input);

        istream_iterator<string> it(strstr);
        istream_iterator<string> end;
        vector<string> results(it, end);

        source_number.setNum(results[0]);
        source_language.setPrecedence(results[1]);
        target_language.setPrecedence(results[2]);
    }

    void compute()
    {
        AlienNumber temp_number;
        temp_number.setNum( ToString(source_language.getFirstChar()) );
        temp_number.setLanguage( source_language );

        int count = 0;

        while(temp_number.getNum() != source_number.getNum())
        {
            temp_number.increment();
            count++;
        }

        target_number.setLanguage(target_language);
        target_number.setNum( ToString(target_language.getFirstChar()));

        for(int i=0; i<count; i++)
        {
            target_number.increment();
        }
    }

    string getTargetNumber() const
    {
        return target_number.getNum();
    }

private:
    Language source_language;
    Language target_language;
    AlienNumber source_number;
    AlienNumber target_number;
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
        v_testCases[i].parseTestCase();
        v_testCases[i].compute();
    }

    for(int i=0; i<numTestCase; i++)
    {
        cout<<"Case #"<<i+1<<": "<<v_testCases[i].getTargetNumber()<<endl;
    }

    return 0;
}
