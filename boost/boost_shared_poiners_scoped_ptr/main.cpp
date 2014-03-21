#include <iostream>
#include <boost/scoped_ptr.hpp>

using namespace std;

/// boost::scoped_ptr - Ќекопируемый автоматический указатель

struct Foo
{
    Foo() { cout << "std-ctor" << endl; }
    ~Foo() { cout << "std-dctor" << endl; }
    void bar() {};
};
int main()
{
    {
        boost::scoped_ptr<Foo> fooPtr(new Foo);
        fooPtr.reset(new Foo);

        fooPtr->bar();
        Foo& objRef = *fooPtr;
        Foo* objPtr = fooPtr.get();
    }
    cout << "return";
    /** std-ctor
        std-ctor
        std-dctor
        std-dctor
        return
    */
    return 0;
}
