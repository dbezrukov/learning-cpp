#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

template <typename InputIterator, typename Predicate>
vector<InputIterator> find_all(InputIterator first, InputIterator last, Predicate pred)
{
    vector<InputIterator> res;

    /// � �������� �������, iterator_traits<_Iterator> -��� ����� ��� ����������� ������������� ���������
    typename iterator_traits<InputIterator>::value_type temp;

    while (true)
    {
        first = find_if(first, last, pred);
        /// ������� �� ����� �������, �������
        if ( first == last )
        {
            break;
        }
        res.push_back( first );
        ++first;
    }
    return res;
}

template <typename T>
class print
{
public:
    void operator()(T x)
    {
        cout << x << endl;
    }
};

template <typename T>
class print<T*> /// ������������� ��� T* ������������� ���������� ������
{
public:
    void operator()(T* x)
    {
        cout << *x << endl;
    }
};

int main()
{
    /// ������ ��� ��������, ������ 5
    int ints[] = { 1, 5, 6, 5, 2, 7, 5 };
    vector<int*> res = find_all(ints, ints+7, bind2nd(equal_to<int>(), 5));
    for_each(res.begin(), res.end(), print<int*>());
    return 0;
}
