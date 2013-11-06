#include <iostream>

using namespace std;

struct Foo
{
    Foo()        { cout << "d"; }
    Foo(int i)   { cout << "i"; }
    Foo(char c)  { cout << "c"; }
    Foo(long l)  { cout << "l"; }
    Foo(float f) { cout << "f"; }
};

int main()
{
    Foo f1('a');
    Foo f2('a'+1);
    Foo f3(1);
    Foo f4(0x01);
    Foo f5(0x001L);
    Foo f6(1.0f);
    /// ciiilf
    return 0;
}
