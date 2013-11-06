#include <iostream>
#include <set>

using namespace std;

int main()
{
    typedef multiset<int> Mymset;
    Mymset mymset;
    mymset.insert(1);
    mymset.insert(2);
    mymset.insert(2);

// �������
    Mymset::iterator ret = mymset.insert(1);
    // ret.second == true - �������� 1 ���������
    cout << "*ret=" << *ret << endl;
    cout << "mymset: ";
    for (Mymset::iterator it = mymset.begin(); it != mymset.end(); ++it)
    {
        cout << *it << " ";
    }
// ��������� � ���������
    cout << endl << "range of 1 : ";
    pair< Mymset::iterator, Mymset::iterator > res = mymset.equal_range( 1 );
    for ( ; res.first != res.second; ++res.first )
    {
        cout << *(res.first) << " ";
    }
    return 0;
}
