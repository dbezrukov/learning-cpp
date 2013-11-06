#include <iostream>

using namespace std;

// public inheritance:
// public -> protected
// protected -> protected
// private -> not accessible

// protected inheritance:
// public -> protected
// protected -> protected
// private -> not accessible

// private inheritance:
// public -> private
// protected -> provate
// provate -> not accessible

// Some programmers abuse this anguage feature, often in combination with multiple inheritance,
// to implement “components” of a class.
// Instead of making an Airplane class that contains an engine data member and a fuselage data member,
// they make an Airplane class that is a protected engine and a protected fuselage. In this way, the
// Airplane doesn’t look like an engine or a fuselage to client code (because everything is protected),
// but it is able to use all of that functionality internally.

class Base
{
public:
    virtual ~Base() {}
    virtual void say() { cout << "base say" << endl; }
};

class Derived : protected Base
{
public:
    virtual ~Derived() {}
    virtual void say() { cout << "derived say" << endl; }

    Base* getPointer() { return this; }
};

int main()
{
    // Такое приведение типа недопустимо
    //Base *pb = new Derived; /// inaccessible base

    // Можно обойти так:
    Derived *pd = new Derived;
    Base *pb = pd->getPointer();
    pb->say();

    return 0;
}
