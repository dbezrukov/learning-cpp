#include <iostream>

using namespace std;

class Foo
{
public:
    void setShared(int val)
    {
        shared = val;
    }
    int getShared() const
    {
        return shared;
    }
protected:
    static int shared;
};

int Foo::shared = 0;

int main()
{
    Foo a;
    a.setShared(12345);

    Foo b;
    cout << "b.getShared=" << b.getShared() << endl;
    return 0;
}
