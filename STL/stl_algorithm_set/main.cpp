#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

/**
Set Algorithms
    Set algorithms are special modifying algorithms that perform set operations (�������� ��� �����������)
    on sequences. They are most appropriate on sequences from set containers,
    but work on sorted sequences from most containers.
    ---------------------------------------------------------------------------------------------------------
    | includes()        |  Determines if one sequence is a subset of another.                               |
    ---------------------------------------------------------------------------------------------------------
    | set_union(),      |  Perform the specified set operations on two sorted sequences,                    |
    | set_intersection()|  copying results to a third sorted sequence.                                      |
    | set_difference(), |                                                                                   |
    | set_symmetric     |                                                                                   |
    |    _difference()  |                                                                                   |
    ---------------------------------------------------------------------------------------------------------

    set - ��������� �������� � ���������������� �����������
    ������� �������� ����������� - �.�. diff( {2}, {2,2} ) = {2}
                                        union( {2}, {2,2} } = {2,2}
*/

template <typename T>
void print(T elem)
{
    cout << elem << " ";
}

template <typename T, typename _InputIterator>
void printContainer(_InputIterator __first, _InputIterator __last, const string& name)
{
    cout << name << ": " ;
    for_each(__first, __last, &print<T>);
    cout << endl;
}

int main()
{
    int ints[] = { 2, 3, 5, 2, 4 };
    int ints2[] = { 1, 2, 7 };

    sort(ints, ints+5);
    sort(ints2, ints2+3);

    printContainer<int>(ints, ints+5, "ints");
    printContainer<int>(ints2, ints2+3, "ints2");

/// includes() - �������� �������� �� �������������
    bool res = std::includes(ints, ints+5, ints2, ints2+3);
    cout << "ints" << (res ? " " : " not ") << "includes ints2" << endl; // not includes

/// set_union - ����������� ��������
    vector<int> intUnion;
    intUnion.resize(8); // ����������� ��������� �������� ������� � �� ��������� �����
    // set_union ���������� ������� ��������������� ���������
    vector<int>::iterator it = set_union(ints, ints+5, ints2, ints2+3, intUnion.begin() );
    printContainer<int>(intUnion.begin(), it, "union"); // 1 2 2 3 4 5 7

/// set_intersection() - ������� ����� ��������
    vector<int> intIntersection;
    intIntersection.resize(5); // �� ������� ����������� ���������
    it = set_intersection(ints, ints+5, ints2, ints2+3, intIntersection.begin());
    printContainer<int>(intIntersection.begin(), it, "intersection"); // 2

/// set_difference() - ���������� �������� ������� ���������, ������� ����������� �� ������
    vector<int> intDiff;
    intDiff.resize(5);
    it = set_difference(ints, ints+5, ints2, ints2+3, intDiff.begin());
    printContainer<int>(intDiff.begin(), it, "difference"); // 2 3 4 5 - �� ������ �� �� ��� ���� ����� ����

/// set_symmetric_difference() - ���������� ��������� ��������� �� ���������� �����������
    /// ������� ���������� ��������
    vector<int> intSymDiff;
    intSymDiff.resize(8);
    it = set_symmetric_difference(ints, ints+5, ints2, ints2+3, intSymDiff.begin());
    printContainer<int>(intSymDiff.begin(), it, "symmetric difference"); // 1 2 3 4 5 7

    return 0;
}
