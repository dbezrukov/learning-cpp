#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>

using namespace std;

void print(int x)
{
    cout << x << " ";
}

int main()
{
    /** Input iterator

    ������ ��� ������ ������, ����� ���� ������� � ������� �� ������� ��������� ��� �����������,
    ���������� ������� �� ������� ��������� �������� ����� ���� �������� � ������� ��������� *,
    ����������� � ���������� �������� ���������� ��������� ��������� ++.
    �������� ������������ ��������� ������� istream_iterator.

    template<class InputIterator, class Function>
    Function for_each (InputIterator first, InputIterator last, Function f)
    {
        while (first != last)
            f(*first++); // ������ �� first
        return f;
    }
    */


    int ints[] = { 1, 2, 3, 4, 5 };
    cout << "Print initial array using for_each & input iterator: ";
    for_each(ints, ints+5, &print);

    /** Output iterator

    ������ ��� �������� �� ������� ������, ���� ��������� ������. ��� ��������� �������������
    ��������� =, *, ++. ������ ��� � ������ ������ ������ � �������, ���� �������� ���������.
    �������� ������������ ������� ���������� ��������� ostream_iterator � ����������� �������
    inserter, font_inserter, back_inserter

    template<class InputIterator, class OutputIterator>
    OutputIterator copy ( InputIterator first, InputIterator last, OutputIterator result )
    {
        while (first!=last)
            *result++ = *first++; // ������ � result
        return result;
    }
    */

    cout << endl << "Print initial array using copy & output iterator: ";
    copy(ints, ints+5, ostream_iterator<int>(cout, " "));

    /** Forward iterator

    ���������� �������� ��������� ����� � ������. ��������� ������ � ������ ������, �������� �� �������
    ��� ������ ��������� ++. ����� ����, �������� ������������ ��������� ��������� == � !=,
    � ����� ��������������� * � ���������� =.

    �������� replace ������ � ��������� ���� ��������� �������� �� ������:

    template <class ForwardIterator, class T>
    void replace (ForwardIterator first, ForwardIterator last, const T& old_value, const T& new_value)
    {
        while (first != last)
        {
            if (*first == old_value) // ������ �� first
                *first = new_value;  // ������ � first
            ++first;
        }
    }
    */

    replace(ints, ints+5, 3, 333);
    cout << endl << "Modify array using replace & forward iterator: ";
    copy(ints, ints+5, ostream_iterator<int>(cout, " ")); /// 1 2 333 4 5

    /** Bidirectional iterator

    ��������� ForwardIterator ����������� ������������ ����� ��������� ��������� --.

    �������� reverse ��������� �������� ��������� ���������

    template<typename BidirectionalIterator>
    void reverse(BidirectionalIterator first, BidirectionalIterator last)
    {
        while (true)
        {
            if (first == last || first == --last)
            {
                return;
            }
            else
            {
                std::iter_swap(first, last);
                ++first;
            }
        }
    }
    */

    reverse(ints, ints+5);
    cout << endl << "Modify array using reverse & bidirectional iterator: ";
    copy(ints, ints+5, ostream_iterator<int>(cout, " ")); /// 5 4 333 2 1

    /** RandomAccessIterator

    ������������� ����������� �������������� ���������, ����������� ���������, ��������������

    */

    ints = { 1, 2, 3, 4, 5 }; /// c++0x feature!
    vector<int> intVec(5);
    vector<int>::iterator it = intVec.begin();
    copy(ints, ints + 5, it);
    cout << endl << "New vector, counting to begin: ";
    cout << *(   it  + 4      ) << ""; /// 5
    cout << *(   it += 3      ) << ""; /// 4
    cout << *(   it -= 1      ) << ""; /// 3
    cout << *(   it  = it - 1 ) << ""; /// 2
    cout << *( --it )           << ""; /// 1

    cout << endl << "Print vector from begin+1 using []: ";
    it++; /// !!!
    for(int i = 0; i < intVec.end()-intVec.begin()-1; i++)
    {
        cout << it[i] << ""; /// 2 3 4 5 - �������������� � ������� � ������� ������ ��������!
    }

    /** reverse_iterator - ������� */

    cout << endl << "Reverse print using reverse_iterator: ";
    copy(intVec.rbegin(), intVec.rend(), ostream_iterator<int>(cout, " "));

    /** stream_iterator - �������

    ������ ����������� ���� �����, ���� �� �������� 555. ������ ��������� ����� ������������ �������

    */

    cout << endl << "Request digits until 555" << endl;
    istream_iterator<int> is(cin);
    ostream_iterator<int> os(cout, " - last entered value\n");

    while( *is != 555)
    {
        *os++ = *is;
        is++ ;
    }

    /** ��������� �������
    inserter - ��������� �������� � ����� ���������
    front_inserter - �� �������� � set, map � vector. ����������������� ������ ������������ � �������� �������
    back_inserver - �� �������� � set � map, ����� ������������ inserter

    �������� ������ � ����� ���������� ������� ����.
    ������� � ������ � ����� �������� {1,2,3}
    ����� � �������� ����� ����� ������ ������� 1,1,1
    */

    int ints0[] = { 0, 0 };
    int intsFront[] = { 3, 2, 1 };
    int intsBack[] = { 1, 2, 3 };
    int intsCenter[] = { 1, 1, 1 };

    list<int> intList(ints0, ints0+2);
    cout << endl << "List initial: ";
    copy(intList.begin(), intList.end(), ostream_iterator<int>(cout, " ")); /// 0 0

    copy(intsFront, intsFront+3, front_inserter(intList));
    cout << endl << "List after front inserter: ";
    copy(intList.begin(), intList.end(), ostream_iterator<int>(cout, " ")); /// 1 2 3 0 0

    copy(intsBack, intsBack+3, back_inserter(intList));
    cout << endl << "List after back inserter: ";
    copy(intList.begin(), intList.end(), ostream_iterator<int>(cout, " ")); /// 1 2 3 0 0 1 2 3

    list<int>::iterator list_it = intList.begin();
    advance(list_it, 4); /// ������ it = it + 4, ���� �������� �� ������������� �������!

    copy(intsCenter, intsCenter+3, inserter(intList, list_it));
    cout << endl << "List after inserter: ";
    copy(intList.begin(), intList.end(), ostream_iterator<int>(cout, " ")); /// 1 2 3 0 1 1 1 0 1 2 3


    /** �������� � �����������

    void advance (InputIterator& iter, Distance& n);
    - ��� ������ ������� ����� ����������������� ��������� iter �� ������������ ����� n:
    ����������: while (n--) ++i;

    void distance(InputIterator& first, InputIterator& second, Distance& n);
    - �������� ���������� ����� ����������� first � second, ��������� ���������� ����� ����� ������ n:
    ����������: return last - first

    */

    return 0;
}
