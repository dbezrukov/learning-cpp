#include <iostream>
#include <algorithm>

using namespace std;

/** template<class ForwardIterator1, class ForwardIterator2>
    ForwardIterator1 find_first_of ( ForwardIterator1 first1, ForwardIterator1 last1,
                                     ForwardIterator2 first2, ForwardIterator2 last2)
    {
        for ( ; first1 != last1; ++first1 )
            for (ForwardIterator2 it=first2; it!=last2; ++it)
                if (*it==*first1)          // or: if (comp(*it,*first)) for the pred version
                    return first1;
        return last1;
    }

    Сложность алгоритма size1*size2

    Для уточнения чем различаются можно использовать алгоритм сравнения mismatch
*/

bool hasIntersect(const int* arr1, const int* arr2, int size1, int size2)
{
    cout << "size1=" << size1 << ", size2=" << size2 << endl;
    const int* res = find_first_of(arr1, arr1+size1, arr2, arr2+size2 );
    return (res != arr1+size1);
}

int main()
{
    int arr1[] = { 'a','b','c','A','B','C' };
    int arr2[] = { 'X','V','A' };
    bool res = hasIntersect(arr1, arr2, sizeof(arr1)/sizeof(int), sizeof(arr2)/sizeof(int));
    cout << "has intersections = " << boolalpha << res;

    return 0;
}
