#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

void print(pair<char, int> elem)
{
    cout << elem.first << "->" << elem.second << endl;
}

void printMap(const string& name, multimap<char,int>& mymultimap)
{
    cout << name << ":" << endl;
    for_each(mymultimap.begin(), mymultimap.end(), &print);
}
int main()
{
    multimap<char,int> mymultimap;
    multimap<char,int>::iterator start, end;

    mymultimap.insert(pair<char,int>('a',10));
    mymultimap.insert(pair<char,int>('b',121));
    mymultimap.insert(pair<char,int>('c',1001));
    mymultimap.insert(pair<char,int>('c',2002));
    mymultimap.insert(pair<char,int>('d',11011));
    mymultimap.insert(pair<char,int>('e',44));

// ������ � ���������
    start=mymultimap.lower_bound ('b');  // itlow points to b
    end=mymultimap.upper_bound ('d');   // itup points to e (not d)

    // print range [itlow,itup):
    for ( ; start != end; ++start )
        cout << start->first << " => " << start->second << endl;

    cout << endl << "test equal_range: "<< endl;
    pair< multimap<char, int>::iterator, multimap<char, int>::iterator > ret;
    ret = mymultimap.equal_range( 'c' );

    for ( ; ret.first != ret.second; ++ret.first )
        cout << (ret.first)->first << "t=> " << (ret.first)->second << endl;

// �������� ���������
    printMap("before delete", mymultimap);
    // ��� ������� 2002 - ����� �������� ����� '�' � � ��� ������� 2002
    ret = mymultimap.equal_range( 'c' );
    for ( ; ret.first != ret.second; ++ret.first )
    {
        if ( (ret.first)->second == 2002 )
        {
            mymultimap.erase( ret.first );
            break;
        }
    }
    printMap("after delete 2002", mymultimap);
    return 0;
}
