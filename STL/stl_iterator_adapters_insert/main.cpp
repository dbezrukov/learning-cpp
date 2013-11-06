#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>

using namespace std;

/** Существут три адаптера
        back_insert_iterator
        front_insert_iterator
        insert_iterator
*/
int main()
{
    /// Дано два вектора. Из первого все числа кроме 10 переписать во второй
    int ints[] = {5, 10, 3, 10, 4, 10};
    vector<int> intVecSrc(ints, ints+6);
    vector<int> intVecDst; /// При использовании back_inserter можно не резервировать размер

/// скопируем элементы в вектор с помощью back_insert_iterator
    back_insert_iterator<vector<int> > intVecDstInserter(intVecDst);

    /// Не модифицирует исходный диапазон, копирует все неудаленные элементы в приёмный диапазон
    /// copy - копируем, а потом удаляем все что равно 10
    remove_copy_if(intVecSrc.begin(), intVecSrc.end(), intVecDstInserter, bind2nd(equal_to<int>(), 10));

    cout << "Src range was not modified: ";
    copy(intVecSrc.begin(), intVecSrc.end(), ostream_iterator<int>(cout, " ") );

    cout << endl << "There is no 10 in dst vector: ";
    copy(intVecDst.begin(), intVecDst.end(), ostream_iterator<int>(cout, " ") );

/// скопируем элементы в set используя insert_iterator
    set<int> intSet;
    insert_iterator<set<int> > intSetInserter(intSet, intSet.begin());

    /// Приёмный диапазон не содержит десятки
    remove_copy_if(intVecSrc.begin(), intVecSrc.end(), intSetInserter, bind2nd(equal_to<int>(), 10));
    ///remove_copy_if(intVecSrc.begin(), intVecSrc.end(), inserter(intSet, intSet.begin()), bind2nd(equal_to<int>(), 10));

    cout << endl << "There is no 10 in dst set: ";
    copy(intSet.begin(), intSet.end(), ostream_iterator<int>(cout, " ") );
    return 0;
}
