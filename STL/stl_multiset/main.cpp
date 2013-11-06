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

// Вставка
    Mymset::iterator ret = mymset.insert(1);
    // ret.second == true - значение 1 добавится
    cout << "*ret=" << *ret << endl;
    cout << "mymset: ";
    for (Mymset::iterator it = mymset.begin(); it != mymset.end(); ++it)
    {
        cout << *it << " ";
    }
// Обращение к интервалу
    cout << endl << "range of 1 : ";
    pair< Mymset::iterator, Mymset::iterator > res = mymset.equal_range( 1 );
    for ( ; res.first != res.second; ++res.first )
    {
        cout << *(res.first) << " ";
    }
    return 0;
}
