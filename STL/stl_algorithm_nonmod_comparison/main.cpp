#include <iostream>
#include <vector>
#include <list>

using namespace std;

/**
Comparison algorithms
    ---------------------------------------------------------------------------------------------------------
    | equal()         |  Determines if two seq are equal by checking if they have the same order of elems.  |
    ---------------------------------------------------------------------------------------------------------
    | mismatch()      |  Returns the first element in each sequence that does not match                     |
    |                 |  the element in the same location in the other sequence.                            |
    ---------------------------------------------------------------------------------------------------------
    | lexicographical |  Compares two sequences to determine their "lexicographical" ordering.              |
    |      _compare() |  Compares each element of the first seq with its equivalent element in the second.  |
    |                 |  If one element is less than the other, that sequence is lexicographically first.   |
    |                 |  If the elements are equal, compares the next elements in order.                    |
    ---------------------------------------------------------------------------------------------------------
*/

int main()
{
    /// Алгоритмы расчитаны на применение контейнеров разных типов
    /// Для одинаковых типов лучше применять операторы > и ==

    vector<int> intVec;
    list<int> intList;

    intVec.push_back( 1 );
    intVec.push_back( 2 );
    intVec.push_back( 3 );

    intList.push_back( 1 );
    intList.push_back( 3 );
    intList.push_back( 2 );

/// equal() - Determines if two seq are equal by checking if they have the same order of elems.
    bool eq = equal(intVec.begin(), intVec.end(), intList.begin());
    if (!eq)
    {
        cout << "Not equal" << endl;

/// mismatch()
        pair<vector<int>::iterator, list<int>::iterator> miss;
        miss = mismatch( intVec.begin(), intVec.end(), intList.begin());
        cout << "The first mismatch is at position " << miss.first - intVec.begin() << endl; // 1
        cout << "The vector has value " << *(miss.first)
             << " and the list has value " << *(miss.second) << endl; // 2 и 3
    }

/// lexicographical_compare() - Проверим кто лексикографически первый
    bool first = lexicographical_compare(intVec.begin(), intVec.end(), intList.begin(), intList.end());
    if (first)
        cout << "vector is first" << endl; // вектор первый
    else
        cout << "list is first" << endl;
    return 0;
}
