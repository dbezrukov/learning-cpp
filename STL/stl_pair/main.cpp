#include <iostream>

using namespace std;

// Для полноценного спользования pair в классах должны быть определены функции == и <.
int main()
{
    pair<string, int> pair1("abc", 1);
    pair<string, int> pair2("aba", 1);

    // Оператор равенства -равно если first и second попарно равны
    // operator==(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
    // { return __x.first == __y.first && __x.second == __y.second; }
    bool eq = ( pair1 == pair2 );
    cout << "eq=" << eq << endl;

    // Оператор <
    // operator<(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
    // { return ( __x.first < __y.first )
    //     || (!( __y.first < __x.first ) && __x.second < __y.second); }
	// Если первый меньше или если первый не меньше, но меньше второй
	// Условно говоря -second это продолжение числа

	bool less1 = ( pair1 < pair2 );
    cout << "less1=" << less1 << endl;
    return 0;
}
