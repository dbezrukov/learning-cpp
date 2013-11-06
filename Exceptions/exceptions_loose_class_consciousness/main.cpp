#include <iostream>

using namespace std;

class A
{
public:
   A() { std::cout << "A::A()\n"; }
   virtual void Foo() { std::cout << "A::Foo()\n"; }
};

class B : public A
{
public:
   B() { std::cout << "B::B()\n"; }
   virtual void Foo() { std::cout << "B::Foo()\n"; }
};

int main()
{
   try
   {
       throw B();
   }
   catch(A ex) /// ����������, ����� ����� �� ��������
   {
       ex.Foo(); /// ���������� A::Foo
   }
   catch(B& ex)
   {
       ex.Foo();
   }
   return 0;
}
