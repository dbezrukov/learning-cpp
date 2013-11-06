#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <math.h>

using namespace std;

/**
Utility Algorithms
   Unlike the other algorithms, the utility algorithms do not work on sequences of data.
   We consider them part of the STL only because they are templatized.
    ---------------------------------------------------------------------------------------------------------
    | min(), max()    |  Return the minimum or maximum of two values.                                       |
    | swap()          |  Swap two values.                                                                   |
    ---------------------------------------------------------------------------------------------------------
Nonmodifying Algorithms
  Search Algorithms (S - must be sorted)
    ---------------------------------------------------------------------------------------------------------
    | find(),         |  Finds the first element that matches a value                                       |
    | find_if()       |  or causes a predicate to return true                                               |
    ---------------------------------------------------------------------------------------------------------
    | find_first_of() |  Like find, except searches for one of several elements at the same time            |
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
  Comparison algorithms
    ---------------------------------------------------------------------------------------------------------
    | equal()         |  Determines if two seq are equal by checking if they have the same order of elems.  |
    ---------------------------------------------------------------------------------------------------------
    | mismatch()      |  Returns the first element in each sequence that does not match                     |
    |                 |  the element in the same location in the other sequence.                            |
    ---------------------------------------------------------------------------------------------------------
    | lexicographical |  Compares two sequences to determine their “lexicographical” ordering.              |
    |      _compare() |  Compares each element of the first seq with its equivalent element in the second.  |
    |                 |  If one element is less than the other, that sequence is lexicographically first.   |
    |                 |  If the elements are equal, compares the next elements in order.                    |
    ---------------------------------------------------------------------------------------------------------
  Operational algorithms
    ---------------------------------------------------------------------------------------------------------
    | for_each()      |  Executes a function on each element in the sequence. Useful for printing elements  |
    ---------------------------------------------------------------------------------------------------------
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
    | rotate(),       |  Swaps the first and second “halves” of the sequence,                               |
    | rotate_copy()   |  either in place or by copying the results to a different sequence.                 |
    |                 |  The two subsequences to be swapped need not be equal in size.                      |
    ---------------------------------------------------------------------------------------------------------
Sorting algorithms
    ---------------------------------------------------------------------------------------------------------
    | sort(),         |  Sorts elements in place, either preserving the order of duplicate elements or not. |
    | stable_sort()   |  The performance of sort() is similar to quicksort, and the performance of          |
    |                 |  stable_sort() is similar to merge-sort (although the exact algorithms may differ)  |
    ---------------------------------------------------------------------------------------------------------
    | partial_sort(), |  Partially sorts the sequence: the first n elements of a fully sorted sequence      |
    | par_sort_copy() |  are sorted, the rest are not. Either in place or by copying them to a new sequence.|
    ---------------------------------------------------------------------------------------------------------
    | nth_element()   |  Relocates the nth element of the sequence as if the entire sequence were sorted.   |
    ---------------------------------------------------------------------------------------------------------
    | merge(),        |  Merges two sorted sequences, either in place or by copying them to a new sequence. |
    | inplace_merge() |                                                                                     |
    ---------------------------------------------------------------------------------------------------------
    | make_heap(),    |  A heap is a standard data structure in which the elements of an array or sequence  |
    | push_heap(),    |  are ordered in a semi-sorted fashion so that finding the “top” element is quick.   |
    | pop_heap(),     |  These four algorithms allow you to use heap-sort on sequences.                     |
    | sort_heap()     |                                                                                     |
    ---------------------------------------------------------------------------------------------------------
    | partition()     |  Sorts the sequence such that all elements for which a predicate returns true are   |
    | stable_partition|  before all elements for which it returns false, either preserving the original     |
    |                 |  order of the elements within each partition or not.                                |
    ---------------------------------------------------------------------------------------------------------
    | random_shuffle  |  “Unsorts” the sequence by randomly reordering the elements.                        |
    ---------------------------------------------------------------------------------------------------------

Set Algorithms
    Set algorithms are special modifying algorithms that perform set operations (операции над множествами)
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
*/

int main()
{
    return 0;
}
