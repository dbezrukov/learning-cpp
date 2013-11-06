#include <iostream>
#include <bitset>

using namespace std;

int main()
{
    bitset<5> mybitset1( string("00010") );
    cout << mybitset1 << endl;

    bitset<5> mybitset2( string("00110") );
    cout << mybitset2 << endl;

    // ����������� '�'
    bitset<5> mybitsetAND = mybitset1 & mybitset2;
    cout << "AND=" << mybitsetAND << endl;

    // ����������� '���'
    bitset<5> mybitsetOR = mybitset1 | mybitset2;
    cout << "OR=" << mybitsetOR << endl;

    // ������� ���� �� ������ �������������� ����
    bool any = mybitset1.any();
    cout << "any=" << any << endl;

    // �����
    mybitset1 <<= 2;
    cout << mybitset1 << endl; // 01000 - ����� ������� �� ��� �������
    return 0;
}
