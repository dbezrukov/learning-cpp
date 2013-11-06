#include <iostream>

using namespace std;

// ��� ������������ ������������ pair � ������� ������ ���� ���������� ������� == � <.
int main()
{
    pair<string, int> pair1("abc", 1);
    pair<string, int> pair2("aba", 1);

    // �������� ��������� -����� ���� first � second ������� �����
    // operator==(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
    // { return __x.first == __y.first && __x.second == __y.second; }
    bool eq = ( pair1 == pair2 );
    cout << "eq=" << eq << endl;

    // �������� <
    // operator<(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
    // { return ( __x.first < __y.first )
    //     || (!( __y.first < __x.first ) && __x.second < __y.second); }
	// ���� ������ ������ ��� ���� ������ �� ������, �� ������ ������
	// ������� ������ -second ��� ����������� �����

	bool less1 = ( pair1 < pair2 );
    cout << "less1=" << less1 << endl;
    return 0;
}
