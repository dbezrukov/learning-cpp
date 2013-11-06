#include <iostream>

using namespace std;

class foo
{
public: int x;
};

class boo
{
public: int y;
};

class derived: public foo, boo
{
};

int main()
{
    derived d;
    d.x;
    d.y;
    return 0;
}
