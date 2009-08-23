
#include <string>
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
