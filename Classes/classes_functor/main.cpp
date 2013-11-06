#include <iostream>
#include <algorithm>
using namespace std;

class PrintFunctor
{
public:
    PrintFunctor()
        : counter( 0 )
    {
        cout << "ctor" << endl;
    }
    PrintFunctor(const PrintFunctor& src)
        : counter( src.counter )
    {
        cout << "copy ctor" << endl;
    }
    void operator()(int x)
    {
        counter++;
        cout << x << endl;
    }
    int counter;
};

void PrintFunction(int x)
{
    std::cout << x << std::endl;
}

template<typename InputIterator, typename Function>
Function my_for_each(InputIterator first, InputIterator last, Function f)
{
    for ( ; first != last; ++first)
    {
        f(*first);
    }
    return f;
}

find_if()

int main()
{
    int x[] = { 1, 2, 3, 4, 5 };

    PrintFunctor print;

    my_for_each(x, x+sizeof(x)/sizeof(int), print);
    cout << "counter=" << print.counter << endl << endl; // 0

    print = my_for_each(x, x+sizeof(x)/sizeof(int), print);
    cout << "counter=" << print.counter << endl; // 5

    my_for_each(x, x+sizeof(x)/sizeof(int), PrintFunction);
    return 0;
}
