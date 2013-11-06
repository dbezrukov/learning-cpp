#include <iostream>
#include <typeinfo>
#include "math.h"
#include "strings.h"

using namespace std;

/**
    In many cases when working with templates, you'll write one generic version for all possible
    data types and leave it at that -every vector may be implemented in exactly the same way.
    The idea of template specialization is to override the default template implementation to handle
    a particular type in a different way.

    —оздадим класс Storage дл€ хранени€ переменной:
    - дл€ переменной типа double изменим вывод и добавим функции управлени€ точностью (full spec)
    - дл€ переменной типа int* реализуем спец. конструктор и деструктор
*/

template <typename T>
class Storage
{
private:
    T _value;
public:
    Storage(T value)
        : _value( value )
    {
    }
    ~Storage()
    {
    }
    void print()
    {
        std::cout << _value << std::endl;;
    }
};

/** Full template specialization for double:
    - setPrecision method added
    - print changed
*/
template <>
class Storage<double>
{
private:
    double _value;
    double _precision;
public:
    Storage(double value)
        : _value( value )
        , _precision( 3 )
    {
    }
    ~Storage()
    {
    }
    void setPrecision(int precision)
    {
        _precision = precision;
    }
    void print()
    {
        cout.setf(std::ios_base::fixed,std::ios_base::floatfield);
        std::cout.precision(_precision);
        cout << _value << std::endl;;
    }
};

/// Specialization of ctor, dctor for char* data type
template <>
Storage<char*>::Storage(char* value)
{
    cout << "ctor Storage<char*>" << endl;
    _value = new char[strlen(value)+1];
    strcpy(_value, value);
}

template <>
Storage<char*>::~Storage()
{
    delete [] _value;
}

/// Partial template specialization for T*
template <typename T>
class Storage<T*>
{
private:
    T* _value;
public:
    Storage(T* value) // for pointer type T
    {
        cout << "ctor Storage<T*>" << endl;
        _value = new T(*value);
    }
    ~Storage()
    {
        delete _value;
    }
    void print()
    {
        std::cout << *_value << std::endl;
    }
};

int main()
{
    Storage<float> test_f( static_cast<float>(M_PI) );
    test_f.print();

/// test full specialization for <double>
    Storage<double> test_d( static_cast<double>(M_PI) );
    test_d.setPrecision(10);
    test_d.print();

/// test partial method specialization for type char*
    char* name = new char [10];
    strcpy(name, "myname");
    Storage<char*> test_pc( name );
    delete [] name;

    /// Ѕез специализации выдаст чушь из-за удалени€ массива
    test_pc.print();

/// проверка специализации шаблона дл€ типа T*
    int x = 7;
    Storage<int*> intPtrStorage(&x);
    /// ¬ыводит значение переменной, а не адрес
    intPtrStorage.print();
    return 0;
}

