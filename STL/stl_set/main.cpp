#include <iostream>
#include <set>
#include <list>

using namespace std;

int main()
{
    typedef set<int> Myset;
    Myset myset;
    myset.insert(1);
    myset.insert(2);
    myset.insert(2);

// �������
    pair<Myset::iterator, bool> ret;
    ret = myset.insert(1);
    // ret.second == false - �������� 1 ��� � ���������
    cout << "ret.second=" << (bool)ret.second << endl;

    // ������� � ������������� ���������� �������� �� ���������� �������
    // ��� �� ������������ ������� ������� �� ��� �������
    Myset::iterator it = myset.insert( myset.begin(), 3 );
    cout << "val=" << *it << endl; // val=3

// �����
    int count = myset.count( 2 );
    cout << "count of 2 is " << count << endl; //count=1

    set<int>::iterator it2 = myset.find( 2 );
    *it = 3;
    cout << "=====" << *it << endl;

// ����������� set � ������
    list<int> mylist;
    cout << "list of set is: ";
    mylist.insert(mylist.begin(), myset.begin(), myset.end());
    for (list<int>::iterator it = mylist.begin(); it != mylist.end(); ++it)
    {
        cout << *it << " ";
    }
    return 0;
}
