#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

/**
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
    int ints[] = { 2, 7, 7, 1, 5, 1 };

/// sort() - алгоритм быстрой сотрировки, по умолчанию используется оператор <, сложность NlogN
    std::sort(ints, ints+6);
    printContainer<int>(ints, ints+6, "ints after sorting");

/// stable_sort() - гарантирует, что сохранится порядок следования двух элементов с одинаковыми значениями

/// merge() - объединяет два отсортированных масива, имеет линейную сложность
    int ints2[] = { 5, 1, 3, 8, 3, 0 };
    std::sort(ints2, ints2+6);
    printContainer<int>(ints2, ints2+6, "ints2             ");

    vector<int> merged;
    merged.resize( sizeof(ints)/sizeof(int) + sizeof(ints2)/sizeof(int));
    merge(ints, ints+6, ints2, ints2+6, merged.begin());
    printContainer<int>(merged.begin(), merged.end(), "merged ");

    /** Для реализации очередей с приоритетами неэффективно использовать списки -время O(n),
        лучше пользоваться сбалансированными деревьями -тогда сложность будет O(logN)
        Время нахождения вершины -константа! На базе алгоритмов heap_ построен priority_queue
    */
    int myints[] = {10,20,30,5,15};
    vector<int> v(myints,myints+5);

    /// Конструкирование heap-структуры, при которой значение сына элемента не может быть больше чем у родителя
    make_heap(v.begin(),v.end());
    cout << "initial max heap   : " << v.front() << endl;

    /// Удалить из heap структуры верхний элемент
    pop_heap(v.begin(),v.end());
    /// Удалить фактически этот элемент из вектора
    v.pop_back();
    cout << "max heap after pop : " << v.front() << endl; // 20

    /// Добавить элемент в частично упорядоченное дерево
    /// сначала добавляем в конец вектора
    v.push_back(99);
    /// последний элемент добавится в дерево
    push_heap(v.begin(),v.end());
    cout << "max heap after push: " << v.front() << endl;

    /// сортировка дерева за NlogN
    sort_heap(v.begin(),v.end());

    cout << "final sorted range :";
    for (unsigned i=0; i<v.size(); i++)
    {
        cout << " " << v[i];
    }
    return 0;
}
