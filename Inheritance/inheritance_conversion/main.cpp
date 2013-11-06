#include <iostream>

using namespace std;

class Foo
{
public:
    virtual ~Foo() {}
};

class Bar     : public Foo  {};
class Bar2    : public Foo  {};
class FooBar  : public Bar  {};
class FooBar2 : public Bar2 {};

int main()
{
    /// FooBar2& fb2 = dynamic_cast<Foo&>(new FooBar2);
    /// Foo& foo2 = new FooBar;
    /// Foo& foo = static_cast<Foo&>(FooBar2 f);

    Foo& foo  = dynamic_cast<Foo&>(*(new FooBar2)); /// ok, берем ссылку на объект, созданный в куче

    /// FooBar2* fb3 = new Foo;
    return 0;
}
