#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    cout.width(5);
    cout.fill('0');
    cout.precision(3);
    cout << 1.12f; /// 01.12
    return 0;
}
