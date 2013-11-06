#include <iostream>
#include <fstream>

using namespace std;

class Foo
{
    friend ostream& operator<<(ostream& ostr, const Foo& foo);
    friend istream& operator>>(istream& istr, Foo& foo);
public:
    Foo()
        : _x(1)
        , _y(2)
    {
    }

protected:
    int _x;
    int _y;
};

/// �������� ������ � �����: cout << foo
/// ���������� ������� �������� �����. ����� �������� <<. ����� cout, ������ ��� ������.
/// ���� �������� � ����� ����������:
ostream& operator<<(ostream& ostr, const Foo& foo)
{
        ostr << "Foo, x=" << foo._x << ", y=" << foo._y;
        return ostr;
}

istream& operator>>(istream& istr, Foo& foo)
{
        istr >> foo._x >> foo._y;
        return istr;
}

int main()
{
    Foo foo;
    cout << "Read object. Type 2 digits:" << endl;
    cin >> foo;
    ///                                        trunc - �������� ����, ����� ������� �����
    fstream fs("foo.txt", ios::out | ios::in | ios::trunc);
    if (!fs.good())
    {
        cout << "file error!" << endl;
        return 1;
    }

    cout << "Write object to file" << endl;
    fs << foo;
    return 0;
}
