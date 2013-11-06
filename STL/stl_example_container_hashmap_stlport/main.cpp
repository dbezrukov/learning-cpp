#include <iostream>
#include <map>

#include "hashmap.h"

int main()
{
    /** ��� ����������� �������� ������� �������� �����������
        ���� �������� ������ ������� ���������, ��� ����� id ������������� ��� ��������
        ��������� ������������ id
        ������������, ���� ��� ������� �� ������ � ���������, ���-���� ��� ���� ������ ������ ����� ��������,
        ������� � ��������� ������� ������. H(key1)=H(key2) -��������� ��������
    */

    hashmap<int, string> myHash;
    myHash.insert( make_pair(2046, "Ivan Petrov") );
    myHash.insert( make_pair(4027, "Olga Sidorova") );

    /// ������ hashmap � �������������� ���������
    for (hashmap<int, string>::iterator it = myHash.begin(); it != myHash.end(); ++it)
    {
        /// ��������� ��������� * � ->
        cout << it->first << " maps to " << (*it).second << endl;
    }

    /// ������ �����������
    map<int, string> myMap(myHash.begin(), myHash.end());
    for (map<int, string>::iterator it = myMap.begin(); it != myMap.end(); ++it)
    {
        cout << it->first << " maps to " << (*it).second << endl;
    }

    return 0;
}
