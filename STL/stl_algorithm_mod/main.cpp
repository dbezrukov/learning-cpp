#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;

/**
Modifying Algorithms
    ---------------------------------------------------------------------------------------------------------
    | transform()     |  Calls a function on each element or each pair of elements.                         |
    ---------------------------------------------------------------------------------------------------------
    | copy(),         |  Copies elements from one sequence to another.                                      |
    | copy_backward() |                                                                                     |
    ---------------------------------------------------------------------------------------------------------
    | iter_swap(),    |  Swap two elements or sequences of elements.                                        |
    | swap_ranges()   |                                                                                     |
    ---------------------------------------------------------------------------------------------------------
    | replace(),      |  Replaces with a new element all elements matching a value                          |
    | replace_if(),   |  or that cause a predicate to return true,                                          |
    | replace_copy(), |  either in place or by copying results to a new sequence.                           |
    | repl_copy_if()  |                                                                                     |
    ---------------------------------------------------------------------------------------------------------
    | fill(),         |  Sets all elements in the sequence to a new value.                                  |
    | fill_n()        |                                                                                     |
    ---------------------------------------------------------------------------------------------------------
    | generate(),     |  Like fill() and fill_n(), except calls a specified function                        |
    | generate_n()()  |  to generate values to place in the sequence.                                       |
    ---------------------------------------------------------------------------------------------------------
    | remove(),       |  Removes from the sequence elements that match a given value                        |
    | remove_if(),    |  or that cause a predicate to return true,                                          |
    | remove_copy(),  |  either in place or by copying results to a different sequence.                     |
    | remov_copy_if() |                                                                                     |
    ---------------------------------------------------------------------------------------------------------
    | unique(),       |  Removes consecutive duplicates from the sequence,                                  |
    | unique_copy()   |  either in place or by copying results to a different sequence.                     |
    ---------------------------------------------------------------------------------------------------------
    | reverse(),      |  Reverses the order of the elements in the sequence,                                |
    | reverse_copy()  |  either in place or by copying the results to a different sequence.                 |
    ---------------------------------------------------------------------------------------------------------
    | rotate(),       |  Swaps the first and second УhalvesФ of the sequence,                               |
    | rotate_copy()   |  either in place or by copying the results to a different sequence.                 |
    |                 |  The two subsequences to be swapped need not be equal in size.                      |
    ---------------------------------------------------------------------------------------------------------

    ¬о всех модифицирующих алгоритмах есть source и destination. „асто они совпадают.
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

/// дл€ примера transform с бинарной функцией
template <typename T>
int sumPair(T x, T y)
{
    cout << x << "-" << y << " ";
    return (x+y);
}

int main()
{
    int ints[] = {1, 3, 7, 5, 2};
    vector<int> intVec(ints, ints+5);
    vector<int> intVec2(ints, ints+5);
    reverse(intVec2.begin(), intVec2.end());

    printContainer<int>(intVec.begin(), intVec.end(), "vec1");
    printContainer<int>(intVec2.begin(), intVec2.end(), "vec2");

/// transform() - Calls a function on each element or each pair of elements.
    //примен€етс€ к каждому элементу множества
    //template < class InputIterator, class OutputIterator, class UnaryOperator >
    //OutputIterator transform ( InputIterator first1, InputIterator last1,
    //                           OutputIterator result, UnaryOperator op );
    transform(intVec.begin(), intVec.end(), intVec.begin(), bind2nd(plus<int>(), 10));
    printContainer<int>(intVec.begin(), intVec.end(), "vec1 after add 10 to each element");

    //примен€етс€ попарно к элементам двух множеств
    //template < class InputIterator1, class InputIterator2, class OutputIterator, class BinaryOperator >
    // OutputIterator transform ( InputIterator1 first1, InputIterator1 last1,
    //                            InputIterator2 first2, OutputIterator result,
    //                            BinaryOperator binary_op );
    transform(intVec.begin(), intVec.end(), intVec2.begin(), intVec.begin(), plus<int>());
    printContainer<int>(intVec.begin(), intVec.end(),   "vec1 after sum pairs");

/// iter_swap()
    printContainer<int>(ints, ints+5, "ints before swap");
    iter_swap(ints, ints+3);
    printContainer<int>(ints, ints+5, "ints after swap");

/// swap_ranges() - swap_ranges(first.begin()+1, first.end()-1, second.begin());

/// replace() - replaces with a new element all elements matching a value
    std::replace(ints, ints+5, 3, 333);
    printContainer<int>(ints, ints+5, "ints after replace 3 with 333 ");

/// replace() - replaces with a new element all elements that cause predicate to return true
    std::replace_if(ints, ints+5, bind2nd(greater<int>(), 5), 0);
    printContainer<int>(ints, ints+5, "ints after replace all greater than 5 with 0");

/// fill() - sets all elements in the sequence to a new value.
    std::fill(ints, ints+5, 5);
    printContainer<int>(ints, ints+5, "ints after fill with 5");

/// fill_n() - fill n element starting from specified iterator
    std::fill_n(ints, 2, 10);
    printContainer<int>(ints, ints+5, "ints after fill first 2 with 10");

///  generate(), generate_n() - calls a specified function to generate values to place in the sequence.::
    std::generate(ints+3, ints+5, rand);
    printContainer<int>(ints, ints+5, "ints after fill with rand"); // 10 10 x y z

/// remove(), remove_if - Removes from the sequence elements that match a given value or that cause a predicate to return true                                          |
    int* it = std::remove(ints, ints+5, 10);
    // remove - возвращает итератор на новый конец последовательности
    printContainer<int>(ints, it, "ints after remove 10"); // x y z

/// unique
    it = std::unique(ints, it);
    printContainer<int>(ints, it, "ints after unique");

/// reverse(), reverse_copy() - Reverses the order of the elements in the sequence,
/// either in place or by copying the results to a different sequence.

    std::reverse(ints, it);
    printContainer<int>(ints, it, "ints after reverse");

    int size = it-ints;
    int* new_seq = new int[size];
    std::reverse_copy(ints, it, new_seq);
    // reverse с сохранением результатов в другую последовательность
    printContainer<int>(new_seq, new_seq+size, "copy of rotated ints");

/// rotate(), rotate_copy() - Swaps the first and second УhalvesФ of the sequence, either in place
/// or by copying the results to a different sequence. The two subsequences to be swapped need not be equal in size.                      |
    // начало середина конец
    printContainer<int>(ints, it, "now rotate ints from 3rd"); // x y z
    std::rotate(ints, ints+2, it);
    printContainer<int>(ints, it, "ints after rotate"); // z x y
    return 0;
}
