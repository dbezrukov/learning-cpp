#include <iostream>

using namespace std;

struct A
{
    virtual void foo() { cout << "A::foo" << endl; }
};

struct B : public A
{
    virtual void foo() { cout << "B::foo" << endl; }
};

int main()
{
    try
    {
        try
        {
            B b;
            throw (b);
        }
        catch(A a)
        {
            a.foo();
            throw; /// пробрасывается исключение типа B
                   /// модифицируется локальная копия a
        }
    }
    catch(A& a)
    {
        a.foo();
    }

    return 0;
}
