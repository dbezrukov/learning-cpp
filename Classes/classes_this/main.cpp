#include <iostream>

using namespace std;

class Foo
{
public:
    Foo(int x)
        : x(x)
    {
        cout << "x=" << this->getValue() << endl;
    }
    int getValue()
    {
        return x;
    }
protected:
    int x;
};

int main()
{
    Foo foo(812);
    return 0;
}
