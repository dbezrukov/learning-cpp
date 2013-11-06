#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <math.h>

using namespace std;

/**
Numerical Processing Algorithms
    ---------------------------------------------------------------------------------------------------------
    | count(),        |  Counts the number of elements matching a value                                     |
    | count_if()      |  or that cause a predicate to return true.                                          |
    ---------------------------------------------------------------------------------------------------------
    | accumulate()    |  “Accumulates” the values of all the elements in a sequence.                        |
    |                 |  The caller can supply a different binary function.                                 |
    ---------------------------------------------------------------------------------------------------------
    | inner_product() |  Similar to accumulate, but works on two sequences.                                 |
    |                 |  Calls a bin func on parallel elements in the sequences, accumulating the result.   |
    |                 |  The default bin func is multiplication. Calculates dot product of the vectors.     |
    ---------------------------------------------------------------------------------------------------------
    | partial_sum()   |  Generates a new sequence in which each element is the sum (or other bin operation) |
    |                 |  of the parallel element, and all preceding elements, in the source sequence.       |
    ---------------------------------------------------------------------------------------------------------
    | adjacent_diff() |  Generates a new seq in which each elem is the difference (or other bin operation)  |
    |                 |  of the parallel element, and its predecessor, in the source sequence.              |
    ---------------------------------------------------------------------------------------------------------
*/

int main()
{
    int ints[] = { 2,5,3,1,3 };
    vector<int> intVec(ints, ints+5);

/// count() - Counts the number of elements matching a value
    // Посчитаем количество троек
    int nThree = std::count(intVec.begin(), intVec.end(),3);
    cout << "count of 3 is: " << nThree << endl; // 2

/// count_if() - Counts the number of elements that cause a predicate to return true
    // Посчитаем количество значений, превышающих три
    int nGreater3 = std::count_if(intVec.begin(), intVec.end(), bind2nd( greater<int>(), 3 ) );
    cout << "count of elements greater than 3 is: " << nGreater3 << endl; // 1

/// accumulate() - Accumulates the values of all the elements in a sequence.
    //template<typename _InputIterator, typename _Tp, typename _BinaryOperation>
    //inline _Tp accumulate(_InputIterator __first, _InputIterator __last,
    //                      _Tp __init, _BinaryOperation __binary_op)
    //{
    //  for (; __first != __last; ++__first)
    //        __init = __binary_op(__init, *__first);
    //  return __init;
    //}

    // считаем среднее геометрическое с использованием алгоритма accumulate
    double mult = std::accumulate( intVec.begin(), intVec.end(), 1, std::multiplies<int>());
    double geoMean = pow(mult, 1.0 / intVec.size());
    cout << "geoMean=" << geoMean << endl;

    // считаем среднее арифметическое с использованием алгоритма accumulate
    mult = accumulate( intVec.begin(), intVec.end(), 0, std::plus<int>());
    double algMean = mult / intVec.size();
    cout << "algMean=" << algMean << endl;

/// inner_product() - Calls a bin func on parallel elements in the sequences, accumulating the result.
    // По умолчанию -скалярное произведение -сумма попарных произведений элементов
    // for (; __first1 != __last1; ++__first1, ++__first2)
	//  __init = __init + (*__first1 * *__first2);
    vector<int> intVec2(ints, ints+5);
    int innerProduct = inner_product( intVec.begin(), intVec.end(), intVec2.begin(), 1);
    cout << "innerProduct=" << innerProduct << endl; // 49

    // обе функции можно переопределить
    innerProduct = inner_product( intVec.begin(), intVec.end(), intVec2.begin(), 1, std::plus<int>(), std::multiplies<int>() );
    cout << "innerProduct=" << innerProduct << endl; // 49

    return 0;
}
