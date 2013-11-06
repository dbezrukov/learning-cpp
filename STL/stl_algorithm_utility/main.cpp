#include <iostream>
#include <algorithm>

using namespace std;

/**
Utility Algorithms
   Unlike the other algorithms, the utility algorithms do not work on sequences of data.
   We consider them part of the STL only because they are templatized.
    ---------------------------------------------------------------------------------------------------------
    | min(), max()    | Return the minimum or maximum of two values.                                        |
    | swap()          | Swap two values.                                                                    |
    ---------------------------------------------------------------------------------------------------------
*/

int main()
{
    int maxval = std::max(1,2);
    cout << "maxval=" << maxval << endl;

    int val1 = 1;
    int val2 = 2;
    std::swap(val1, val2);
    cout << "val1=" << val1 << endl;

    return 0;
}
