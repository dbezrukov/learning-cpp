#include <iostream>
#include <stdio.h>
#include <string.h>

/** ��� ������������������ ������ ������� �������� ���������:
    - ����������
    - ��������
    - ���������
    - ����������
    - ������
*/

/// lhs - left hand side
/// rhs - right hand side

using namespace std;

template <typename T>
class Array
{
public:
    /// ����������� �� ���������
    Array() {};
    /// ����������� � ����������
    Array(T array[]);
    /// �������� ���������� ��� �������� ������
    T& operator[](int pos);
    /// �������� ���������� ��� ������������ �������
    const T& operator[](int pos) const;
    /// �������� �����������
    Array<T>& operator=(const Array<T>& rhs);
    /// �������� ��������
    template <typename E>
    friend Array<E> operator+(const Array<E>& lhs, const Array<E>& rhs);
    /// �������� ���������
    template <typename E>
    friend bool operator>=(const Array<E>& lhs, const Array<E>& rhs);
    /// �������� ������
    template <typename E>
    friend ostream& operator<<(ostream& ostr, const Array<E>& rhs);
protected:
    static const int maxSize = 10;
    T _array[maxSize];
private:
    /// ����������� �����������. ��������� �������� �� �������
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

    /// ������ �������� �� ��������
    /// printByVal( array1 ); ///�� ��������������!

    /// ����� ���������� �� ������
    printByRef( array1 ); /// ��

    /// ��������� ���������, ������� ���������
    int ints2[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    Array<int> array2( ints2 );

    bool res = array1 >= array2;
    cout << (res ? "array1 >= array2" : "array1 < array2") << endl;

    Array<int> array3;
    array3 = array1 + array2;
    printByRef( array3 );

    return 0;
}
