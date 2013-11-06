#include <iostream>

using namespace std;

/// Overriding is the concept of runtime polymorphism while,
// Overloading is the concept of compile time polymorphism..

/// This code demonstrates method overloading

class Base
{
public:
    Base() : baseNum(0) {};
    virtual ~Base() {};
    void foo(int x) { cout << "foo(int x)" << endl; };
    void bar(int x) { cout << "bar(int x)" << endl; };

    virtual void test() { cout << "Base::test" << endl; }
private:
    int baseNum;
};

class Derived : public Base
{
public:
    Derived() : baseNum(123) {};
    virtual ~Derived() {};
    void foo(float x) { cout << "foo(float x)" << endl; };

    using Base::bar; /// ��� ������������� using ������ ����������� �����������
    void bar(float x) { cout << "bar(float x)" << endl; };

    virtual void test() { cout << "Derived::test" << endl; }
private:
    float baseNum;
};

int main()
{
    Derived derived;
    // 1 - baseNum ��������� � ����������� ������
    // foo - ���������� � �����������
    int x;
    derived.foo(x);
    // bar - ����������� � �����������
    derived.bar(x);

    // ������� ����� ��������� �������� ������ ��� ������������� ���������� � ������
    Base& base1 = derived;
    base1.test(); // Derived::test

    // ��� ����������� ���������� ���������� (SLICING):
    Base base2 = derived;
    base2.test(); // Base::test

    return 0;
}
