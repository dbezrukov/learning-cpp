#include <iostream>
#include <boost/shared_ptr.hpp>

using namespace std;

/// boost::shared_ptr - ���������� ����������� ��������� �� ������, ������ ����������� ������. ������� ������

struct Foo
{
    Foo() { cout << "std-ctor" << endl; }
    ~Foo() { cout << "std-dctor" << endl; }
    void bar() {};
};
int main()
{
    boost::shared_ptr<Foo> fooPtr1;
    {
        boost::shared_ptr<Foo> fooPtr2(new Foo);
        fooPtr2->bar();
        fooPtr1 = fooPtr2; /// �������� ���������
        cout << "exit foo2 scope" << endl;
    }

    fooPtr1->bar();
    fooPtr1.reset(); /// ��������� ������������ � ������ ��������� �.�. ������ �� ���� ������ ���
    cout << "return" << endl;
    /** std-ctor
        std-ctor
        std-dctor
        std-dctor
        return
    */
    return 0;
}
