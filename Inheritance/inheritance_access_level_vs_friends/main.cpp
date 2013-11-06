#include <iostream>

using namespace std;

class Base
{
public:    int a;
protected: int b;
private:   int c;
};

class Derived: Base
{
    friend class Friend;
    int d;
};

class Friend
{
    Derived derived;
    void bar()
    {
        derived.a;
        derived.b;
        //derived.c; - no access
        derived.d;
    }
};

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
