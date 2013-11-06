#include <iostream>

using namespace std;

template<class T>
void foo(T op1, T op2)
{
     std::cout << "op1=" << op1 << std::endl;
     std::cout << "op2=" << op2 << std::endl;
}

template<class T>
struct sum
{
    static void foo(T op1, T op2)
    {
        std::cout << "op1=" << op1 << std::endl;
        std::cout << "op2=" << op2 << std::endl;
    }
};

int main()
{
    foo(1, 3);
    foo<int>(1, '3'); /// создается функция foo(int, int)
    sum::foo(1, 2); /// failed - нужно sum<int>!!!
    return 0;
}
