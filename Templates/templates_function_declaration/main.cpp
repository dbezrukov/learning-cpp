#include <iostream>

using namespace std;

template <class T, class C> void foo(T op1, C op2) {};
template <class C, class T> void foo(C op1, T op2) {};
template <class T, class C> void foo(C op1, T op2) {};

int main()
{
    /// � �������� ����� ������ �� ������ -� ������� 1 � 2
    /// �������� ���� � ����!
    return 0;
}
