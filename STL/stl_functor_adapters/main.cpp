#include <iostream>
#include <algorithm>
#include <functional>
#include <list>

using namespace std;

class Foo
{
public:
    Foo(int x)
        : x ( x )
    {

    }
    void print()
    {
        cout << x << endl;
    }
protected:
    int x;
};

class IsAlpha
{
public:
    bool operator()(int c)
    {
        return (isalpha(c));
    }
};

class IsAlphaUnary : public unary_function<int, bool>
{
public:
    bool operator()(int c) const
    {
        return (isalpha(c));
    }
};

int main()
{
    list<int> mylist;
    mylist.push_back(5);
    mylist.push_back(10);
    mylist.push_back(15);
    mylist.push_back(20);

/// ФУНКЦИОНАЛЬНЫЕ АДАПТЕРЫ
/// связка
    /// найти в списке int число, большее 10
    /// второй операнд greater(x, 10)
    list<int>::iterator it_2nd = find_if(mylist.begin(), mylist.end(), bind2nd(greater<int>(), 10) );
    /// первый операнд greater(10, x)
    list<int>::iterator it_1st = find_if(mylist.begin(), mylist.end(), bind1st(greater<int>(), 10) );

    cout << "it_2nd="<< *it_2nd << endl; // 15
    cout << "it_1st="<< *it_1st << endl; // 5

/// инверторы
    /// найти первый элемент, который не меньше 5
    list<int>::iterator it_not = find_if(mylist.begin(), mylist.end(), not1( bind2nd( less_equal<int>(), 5)));
    cout << "it_not="<< *it_not << endl; // 5

/// вызов функции-члена
    list<Foo> fooList;
    fooList.push_back( Foo(1) );
    fooList.push_back( Foo(2) );

    for_each(fooList.begin(), fooList.end(), mem_fun_ref( &Foo::print) );

    /// список указателей
    list<Foo*> fooPtrList;
    fooPtrList.push_back( new Foo(11) );
    fooPtrList.push_back( new Foo(22) );

    for_each(fooPtrList.begin(), fooPtrList.end(), mem_fun( &Foo::print) );

/// использование обычных глобальных функций
    mylist.push_back( 'A' );
    list<int>::iterator it_alpha = find_if( mylist.begin(), mylist.end(), ptr_fun(::isalpha) );
    cout << "it_alpha="<< static_cast<char>(*it_alpha) << endl; // A

    it_alpha = find_if( mylist.begin(), mylist.end(), IsAlpha() ); // not1 не даст
    cout << "it_alpha="<< static_cast<char>(*it_alpha) << endl; // A

/// ЧТОБЫ ИСПОЛЬЗОВАТЬ ФУНКЦИОНАЛЬНЫЕ АДАПТЕРЫ СО СВОИМИ ФУНКТОРАМИ, ФУНКТОРЫ НУЖНО НАСЛЕДОВАТЬ
/// ОТ unary_function или binary_function.
    list<int>::iterator it_notalpha = find_if( mylist.begin(), mylist.end(), not1( IsAlphaUnary() ) );
    cout << "it_notalpha="<< *it_notalpha << endl; // A

    return 0;
}
