#include <iostream>
#include <stdio.h>
#include <string.h>

/** ƒл€ шаблонизированного класса массива написать операторы:
    - индексации
    - сложени€
    - сравнени€
    - присвоени€
    - вывода
*/

/// lhs - left hand side
/// rhs - right hand side

using namespace std;

template <typename T>
class Array
{
public:
    ///  онструктор по умолчанию
    Array() {};
    ///  онструктор с параметром
    Array(T array[]);
    /// оператор индексации дл€ обычного случа€
    T& operator[](int pos);
    /// оператор индексации дл€ константного объекта
    const T& operator[](int pos) const;
    /// оператор копировани€
    Array<T>& operator=(const Array<T>& rhs);
    /// оператор сложени€
    template <typename E>
    friend Array<E> operator+(const Array<E>& lhs, const Array<E>& rhs);
    /// оператор сравнени€
    template <typename E>
    friend bool operator>=(const Array<E>& lhs, const Array<E>& rhs);
    /// оператор вывода
    template <typename E>
    friend ostream& operator<<(ostream& ostr, const Array<E>& rhs);
protected:
    static const int maxSize = 10;
    T _array[maxSize];
private:
    ///  онструктор копировани€. «апрещаем передачу по значеню
    Array(const Array<T>& src);
};

template <typename T>
Array<T>::Array(T array[])
{
    memcpy(_array, array, maxSize*sizeof(T));
}

//template <typename T>
//Array<T>::Array(const Array<T>& src)
//{
//    memcpy(_array, src._array, maxSize*sizeof(T));
//}

template <typename T>
T& Array<T>::operator[](int pos)
{
    return _array[pos];
}

template <typename T>
const T& Array<T>::operator[](int pos) const
{
    return _array[pos];
}

template <typename T>
Array<T>& Array<T>::operator=(const Array<T>& rhs)
{
    if ( this == &rhs )
        return *this;
    memcpy(_array, rhs._array, maxSize*sizeof(T));
    return *this;
}

template <typename T>
Array<T> operator+(const Array<T>& lhs, const Array<T>& rhs)
{
    T newarray[Array<T>::maxSize];
    for (int i=0; i<Array<T>::maxSize; i++)
    {
        newarray[i] = lhs[i] + rhs[i];
    }
    Array<T> sumArray(newarray);
    return sumArray;
}

template <typename T>
bool operator>=(const Array<T>& lhs, const Array<T>& rhs)
{
    for (int i=0; i<Array<T>::maxSize; i++)
    {
        if ( lhs[i] < rhs[i] )
            return false;
    }
    return true;
}

template <typename T>
ostream& operator<<(ostream& ostr, const Array<T>& rhs)
{
    ostr << "Array=";
    for (int i=0; i<Array<T>::maxSize; i++)
    {
        ostr << rhs[i] << " ";
    }
    return ostr;
}

template <typename T>
void printByVal(Array<T> array)
{
    cout << array << endl;
}

template <typename T>
void printByRef(Array<T>& array)
{
    cout << array << endl;
}

int main()
{
    int ints[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    Array<int> array1( ints );

    /// «апрет передачи по значению
    /// printByVal( array1 ); ///не скомпилируетс€!

    /// ћожно передавать по ссылке
    printByRef( array1 ); /// ок

    /// ѕровер€ем операторы, выводим результат
    int ints2[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    Array<int> array2( ints2 );

    bool res = array1 >= array2;
    cout << (res ? "array1 >= array2" : "array1 < array2") << endl;

    Array<int> array3;
    array3 = array1 + array2;
    printByRef( array3 );

    return 0;
}
