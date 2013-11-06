#include <iostream>
#include <algorithm>
#include <functional>
#include <queue>
#include <list>

using namespace std;

/** 1 Функторы следует делать максимально адаптируемыми, наследуя от unary_function и binary_function
    2 В функторах операция копирования должна быть реализована очень эффективно
    3 Поскольку функциональные объекты передаются по значению, применение виртуальных функций затруднено.
      Чтобы избежать расслоения, сделует пользоваться идиомой pImpl -за внешне мономорфным классом будет
      скрыта богатая функциональность.
*/

template <class Arg1, class Arg2, class Result>
struct _binary_function
{
    typedef Arg1 first_argument_type;
    typedef Arg2 second_argument_type;
    typedef Result result_type;
};

template <class T>
struct _multiplies : _binary_function <T,T,T>
{
    T operator() (const T& x, const T& y) const
    {
        return x*y;
    }
};

template <class Arg, class Result>
struct _unary_function
{
    typedef Arg argument_type;
    typedef Result result_type;
};

class _print_functor : _unary_function<int, void>
{
public:
    void operator()(int x)
    {
        cout << x << endl;
    }
};

void _print_function(int x)
{
    cout << x << endl;
}

int main()
{
    // Использование стандартного функтора "умножение"
    _multiplies<int> multiplicator;
    int x = multiplicator(2, 5);
    cout << "x=" << x << endl; // 10

    // вывести priority_queue так, чтобы элементы были отсортированы по возростанию
    // template < class T, class Container = vector<T>, class Compare = less<typename Container::value_type> >
    // class priority_queue;
    priority_queue< int, vector<int>, greater<int> > myGreaterQueue;
    myGreaterQueue.push( 2 );
    myGreaterQueue.push( 1 );
    myGreaterQueue.push( 3 );

    while ( !myGreaterQueue.empty() )
    {
        cout << myGreaterQueue.top() << endl;
        myGreaterQueue.pop();
    }

    cout << "Test functors" << endl;
    list<int> mylist;
    mylist.push_back( 2 );
    mylist.push_back( 3 );
    mylist.push_back( 5 );

    /// передача функции и функтора дают одинаковый результат
    for_each(mylist.begin(),  mylist.end(), _print_functor());
    for_each(mylist.begin(),  mylist.end(), _print_function);

    /*
    template<typename _InputIterator, typename _Function>
    _Function for_each(_InputIterator __first, _InputIterator __last, _Function __f)
    {
      for (; __first != __last; ++__first)
        __f(*__first);
      return _GLIBCXX_MOVE(__f);
    }
    */
    return 0;
}
