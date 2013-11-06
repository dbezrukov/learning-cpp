#include <iostream>

using namespace std;

/** ������� ������ ������ ����������� const-�����������
    � ������������ �����.
    ������������ ����������� �� ��������� ��������� const-������
*/
class Foo
{
public:
    Foo()
    {
        cout << "std ctor" << endl;
    }
    Foo(Foo& src) /// -��� �������������� ����������� ����������� �����������!
    {
        cout << "copy ctor" << endl;
    }
    Foo(const Foo& src)
    {
        cout << "const copy ctor" << endl;
    }
};



int main()
{
    Foo a;
    Foo b(a); /// ��� const -������� ����� ������ const-������ ������������
    return 0;
}
