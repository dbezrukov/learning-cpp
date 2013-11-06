#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
Operational algorithms
    ---------------------------------------------------------------------------------------------------------
    | for_each()      |  Executes a function on each element in the sequence. Useful for printing elements  |
    ---------------------------------------------------------------------------------------------------------
*/

class MinAndMax : public unary_function<int, void>
{
public:
    MinAndMax();
    void operator() (int elem);
    int min, max;
protected:
    bool first;
};

MinAndMax::MinAndMax()
    : min(-1)
    , max(-1)
    , first(true)
{
}

void MinAndMax::operator()(int elem)
{
    if ( first )
    {
        min = max = elem;
    }
    else if ( elem > max )
    {
        max = elem;
    }
    else if ( elem < min )
    {
        min = elem;
    }
    first = false;
}

template <typename T>
void print(T& elem)
{
    cout << elem << " ";
}


template <typename T>
class Print
{
public:
    void operator()(T& elem)
    {
        cout << elem << " ";
    }
};


int main()
{
/// for_each - Apply function to range (template function)
    //template<typename _InputIterator, typename _Function>
    //_Function for_each(_InputIterator __first, _InputIterator __last, _Function __f)
    //{
    //    for (; __first != __last; ++__first)
    //    __f(*__first);
    //    return _GLIBCXX_MOVE(__f);
    //}

    int ints[] = { 1, 3, 7, 5, 2 };
    vector<int> intVec(ints, ints+5);

    /// Печать с использованием функции
    for_each(intVec.begin(), intVec.end(), print<int>);
    cout << endl;

    /// Печать с использованием функционального объекта
    for_each(intVec.begin(), intVec.end(), Print<int>());
    cout << endl;

    /// Поиск мин и макс элементов
    cout << "finding min and max:" << endl;
    MinAndMax func;
    func = for_each( intVec.begin(), intVec.end(), func);
    cout << "min=" << func.min << endl;
    cout << "max=" << func.max << endl;

    return 0;
}
