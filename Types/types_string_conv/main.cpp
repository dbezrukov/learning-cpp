#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    vector<string> vec;
    vec.push_back("Foo");
    vec.push_back("Bar");
    vec.push_back("Baz");
    vec.push_back("Bee");

    cout << count_if(vec.begin(),
                     vec.end(),
                     bind2nd(greater<string>(), "Baz"));

    //std::string s("hello word");
    //char* c = s.c_str();
    /// нельзя const-значение присваивать обычному
    return 0;
}
