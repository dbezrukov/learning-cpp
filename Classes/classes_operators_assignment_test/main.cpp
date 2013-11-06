#include <iostream>

using namespace std;

/// Порядок вычисления '+' и '-' СЛЕВА НАПРАВО!
struct Foo
{
    //X& operator=(const X& rhs);
    //const X& operator+(const X& rhs) const;
    //const X& operator+(int m);
    Foo(string s)
       : _s(s)
    {
        cout << "ctor: " << _s << endl;
    };
    Foo(const Foo& src)
       : _s( src._s )
    {
        cout << "  copy-ctor: " << _s << endl;
    };
    const Foo operator+(const Foo& foo) const
    {
        cout << " oper: " << _s << endl;
        Foo tmp( string(_s) + string(foo._s));
        return tmp;
    }
    string _s;
};
int main()
{
    Foo a("a"), b("b"), c("c");
    Foo d = a + b + c;
    cout << "Result object: " << d._s;
    /**
    ctor: a
    ctor: b
    ctor: c
     oper: a
    ctor: ab
     oper: ab
    ctor: abc
    Result object: abc
    */

/// a t t t

    return 0;
}
