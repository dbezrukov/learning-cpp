#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>

using namespace std;

/** ��������� ��� ��������
        back_insert_iterator
        front_insert_iterator
        insert_iterator
*/
int main()
{
    /// ���� ��� �������. �� ������� ��� ����� ����� 10 ���������� �� ������
    int ints[] = {5, 10, 3, 10, 4, 10};
    vector<int> intVecSrc(ints, ints+6);
    vector<int> intVecDst; /// ��� ������������� back_inserter ����� �� ������������� ������

/// ��������� �������� � ������ � ������� back_insert_iterator
    back_insert_iterator<vector<int> > intVecDstInserter(intVecDst);

    /// �� ������������ �������� ��������, �������� ��� ����������� �������� � ������� ��������
    /// copy - ��������, � ����� ������� ��� ��� ����� 10
    remove_copy_if(intVecSrc.begin(), intVecSrc.end(), intVecDstInserter, bind2nd(equal_to<int>(), 10));

    cout << "Src range was not modified: ";
    copy(intVecSrc.begin(), intVecSrc.end(), ostream_iterator<int>(cout, " ") );

    cout << endl << "There is no 10 in dst vector: ";
    copy(intVecDst.begin(), intVecDst.end(), ostream_iterator<int>(cout, " ") );

/// ��������� �������� � set ��������� insert_iterator
    set<int> intSet;
    insert_iterator<set<int> > intSetInserter(intSet, intSet.begin());

    /// ������� �������� �� �������� �������
    remove_copy_if(intVecSrc.begin(), intVecSrc.end(), intSetInserter, bind2nd(equal_to<int>(), 10));
    ///remove_copy_if(intVecSrc.begin(), intVecSrc.end(), inserter(intSet, intSet.begin()), bind2nd(equal_to<int>(), 10));

    cout << endl << "There is no 10 in dst set: ";
    copy(intSet.begin(), intSet.end(), ostream_iterator<int>(cout, " ") );
    return 0;
}
