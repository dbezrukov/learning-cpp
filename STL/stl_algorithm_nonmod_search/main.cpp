#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
Search Algorithms (S - must be sorted)
    ---------------------------------------------------------------------------------------------------------
    | find(),         |  Finds the first element that matches a value                                       |
    | find_if()       |  or causes a predicate to return true                                               |
    ---------------------------------------------------------------------------------------------------------
    | find_first_of() |  Like find, except searches for one of several elements at the same time (intersect)|
    ---------------------------------------------------------------------------------------------------------
    | adjacent_find() |  Finds the first instance of two consecutive elements that are equal to each other  |
    ---------------------------------------------------------------------------------------------------------
    | search(),       |  Finds the first (search())                                                         |
    | find_end()      |  or last (find_end()) subsequence in a sequence that matches another sequence       |
    ---------------------------------------------------------------------------------------------------------
    | search_n()      |  Finds the first instance of n consecutive elements that are equal to a given value |
    ---------------------------------------------------------------------------------------------------------
    | lower_bound(),  S  Finds the beginning, (lower_bound()),                                              |
    | upper_bound(),  S  end (upper_bound()),                                                               |
    | equal_range()   S  or both sides (equal_range()) of the range including a specified element           |
    ---------------------------------------------------------------------------------------------------------
    | binary_search() S  Finds a value in a sorted sequence                                                 |
    ---------------------------------------------------------------------------------------------------------
    | min_element(),  |  Finds the minimum                                                                  |
    | max_element()   |  or maximum element in a sequence                                                   |
    ---------------------------------------------------------------------------------------------------------
*/

// for find_if example
bool goodMark(int mark)
{
    return ( mark >= 4 );
}

int main()
{
    int elems[] = {5, 6, 9, 8, 8, 10, 6, 9};
    vector<int> intVec(elems, elems+8);

/// find - Finds the first element that matches a value
   //template <class InputIterator, class T>
   //InputIterator find ( InputIterator first, InputIterator last, const T& value );
    vector<int>::iterator it = std::find( intVec.begin(), intVec.end(), 3);
    if ( it != intVec.end() )
    {
        cout << "found element, value=" << *it << endl; //3
    }

/// find_if - Find the first element that causes a predicate to return true
    //template<class InputIterator, class Predicate>
    //InputIterator find_if ( InputIterator first, InputIterator last, Predicate pred )
    //{
    //  for ( ; first!=last ; first++ )
    //  {
    //      if ( pred(*first) ) break;
    //  }
    //  return first;
    //}
    it = std::find_if( intVec.begin(), intVec.end(), goodMark);
    if ( it != intVec.end() )
    {
        cout << "found good mark, value=" << *it << endl; // 5
    }

/// find_first_of() - Like find, except searches for one of several elements at the same time
    // Первая форма. Ищем первый попавшийся из двух указанных элементов - применяется оператор ==
    int targets[] = {12, 9};
    it = find_first_of( intVec.begin(), intVec.end(), targets, targets + 2);
    if (it != intVec.end())
    {
        cout << "found one of 12 or 9: " << *it << endl; // 9
    }
    // Вторая форма. Ищем первый элемен который больше 12 или 9 - применяется ПРЕДИКАТ
    it = find_first_of( intVec.begin(), intVec.end(), targets, targets + 2, std::greater<int>());
    if (it != intVec.end())
    {
        cout << "found the elem which greater than 8 or 9: " << *it << endl; // 10
    }

/// adjacent_find() - Finds the first instance of two consecutive elements that are equal to each other
    // Ищем первую пару одинаковых элементов
    it = adjacent_find( intVec.begin(), intVec.end());
    if (it != intVec.end())
    {
        cout << "found two consecutive equal elements of value " << *it << endl;
    }

/// search() - Finds the first subsequence in a sequence that matches another sequence
    // Ищем первое вхождение заданной последовательности
    int sub[] = {6, 9};
    it = search( intVec.begin(), intVec.end(), sub, sub + 2);
    if (it != intVec.end())
    {
        cout << "found first subsequence 6, 9 at position " << it - intVec.begin() << endl; //1
    }

/// find_end() - Finds the last subsequence in a sequence that matches another sequence
    // Ищем последнее вхождение заданной последовательности
    it = find_end( intVec.begin(), intVec.end(), sub, sub + 2);
    if (it != intVec.end())
    {
        cout << "found last subsequence 6, 9 at position " << it - intVec.begin() << endl; //6
    }

/// search_n() - Finds the first instance of n consecutive elements that are equal to a given value
    // Ищем первое появление двух чисел больше шести
    // вызов предиката: __binary_pred(*__first, __val)
    it = search_n( intVec.begin(), intVec.end(), 2, 6, std::greater<int>() );
    if (it != intVec.end())
    {
        cout << "found two consecutive values which greater than 6: " << it - intVec.begin() << endl;
    }

/// lower_bound() - Finds the beginning of the range
/// upper_bound() - Finds the end of the range
/// equal_range() - Finds the both sides of the range including a specified element

    // Отсортируем
    std::sort( intVec.begin(), intVec.end() );

    vector<int>::iterator it_lower = lower_bound( intVec.begin(), intVec.end(), 8 );
    vector<int>::iterator it_upper = upper_bound( intVec.begin(), intVec.end(), 8 );

    cout << "8 starts at position: " << it_lower - intVec.begin() << endl; //3
    cout << "8 ends at position: "   << it_upper - intVec.begin() << endl; //5

    pair<vector<int>::iterator,vector<int>::iterator> bounds;
    bounds = std::equal_range( intVec.begin(), intVec.end(), 8 );
    cout << "bounds containing 8: from " << bounds.first  - intVec.begin()
                               << " to " << bounds.second - intVec.begin() << endl; // from 3 to 5

/// max_element - Finds the max element
    cout << "The max element is 8 ends at position: "   << it_upper - intVec.begin() << endl; //5
    return 0;
}
