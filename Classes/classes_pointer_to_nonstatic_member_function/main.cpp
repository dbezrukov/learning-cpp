#include <iostream>

using namespace std;

class Foo
{
public:
    void bar(int& x)
    {
        cout << "bar, x=" << x << endl;
    }
};

typedef void (Foo::*PtrToBar) (int&);

/*
void testPtr(PtrToBar ptrToBar)
{
    Foo a;
    int value = 5;
    (a.*ptrToBar)(value);
}
*/

int main()
{
    PtrToBar methodPtr = &Foo::bar;

    Foo a;
    int value = 5;
    (a.*methodPtr)(value);

    //testPtr(methodPtr);
    return 0;
}
