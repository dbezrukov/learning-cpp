#include <iostream>

using namespace std;

/** AUTO
    The auto keyword deduces the type of a declared variable from its initialization expression.
    auto declarator initializer;
*/

/** VOLATILE
    The volatile keyword is a type qualifier used to declare that an object can be modified
    in the program by something such as the operating system, the hardware, or a concurrently executing thread.
    volatile declarator;

    ����� ���������� �� ��������������, ��������� �� �������� ����� ���� �������� �����.
    ������� ����� ��������� �������� � ����� ���� ������������ ��� locks/releases ������ � ������������� �����������.

    Volatile ��������� � ����������� ������� � ���, ��� ����������������� ���� ��������� �������������� ������,
    ������ �� ����� ���� ������� �����. ��� ����, ������ ������ ��� �����������.
*/

/** REGISTER
    The register keyword specifies that the variable is to be stored in a machine register, if possible.
*/

int main()
{
    auto int x; /// auto �������� ����� � C++0x, ������ �� ������ �������

    volatile int v;

/// volatile + pointers

    volatile char* vpch;
    char* volatile pchv;

/// register
    register int var;

    return 0;
}
