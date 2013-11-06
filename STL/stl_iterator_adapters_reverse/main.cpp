#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    //             0  1  2  3  4  5
    int ints[] = { 1, 3, 2, 5, 7, 6 };
    vector<int> intVec(ints, ints+6);

    vector<int>::iterator it = find(intVec.begin(), intVec.end(), 6);
    cout << "Found 3 at position " << it - intVec.begin() << endl; /// position 5

    vector<int>::reverse_iterator rit = find(intVec.rbegin(), intVec.rend(), 6);

    /// rit.base for the first element returns it.end, so we have to substract 1 from rit.base
    it = rit.base() - 1;

    cout << "Found 3 at position " << it - intVec.begin() << endl;

    return 0;
}
