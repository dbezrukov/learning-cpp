#include <iostream>

using namespace std;

class X
{
public:
    X& operator=(const X& rhs)
    {
        return *this;
    }
    const X& operator+(const X& rhs) const
    {
        return *this;
    }
    const X& operator+(int m)
    {
        return *this;
    }
private:
    int n;
};

int main()
{
    X a, b, c;
    a = a + 5 + c;
    a = a = b + c;
    a = b + 5;

    ///a = b + c + 5;
    /// �������� ������������ this � ������������� �����!!!
    /// ������ � ������������ (b+c) �������� ������������� ����� operator+(int)

    ( c = a + a ) = b + c;

    return 0;
}
