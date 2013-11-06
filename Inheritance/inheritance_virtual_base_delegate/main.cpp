#include <iostream>

using namespace std;

class Base
{
public:
    virtual void foo() = 0;
    virtual void bar() = 0;
 };

class Der1 : public virtual Base
{
public:
    virtual void foo()
    {
        cout << "Der1::foo, calling bar().." << endl;
        bar();
    }
};

class Der2 : public virtual Base
{
public:
    virtual void bar()
    {
        cout << "Der2::bar" << endl;
    }
 };

class Join : public Der1, public Der2
{
};

int main()
{
    cout << "test join" << endl;
    Join* p = new Join(); /// foo implemented in Der1, bar implemented in Der2
    p->foo(); /// делегация вызова брату Der2 !!!

    cout << "test der1" << endl;
    Der1* pDer1 = p;
    pDer1->foo(); /// то же самое

    cout << "test base" << endl;
    Base* pBase = p;
    pBase->foo(); /// вызор реализаций в Der1 и Der2
    pBase->bar();

    return 0;
}
