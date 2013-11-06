#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;

int main()
{
    vector<int> intVec;

    /// читаем числа из стандартного ввода пока не закончатся
    ///  stdin                       eof
  //copy(istream_iterator<int>(cin), istream_iterator<int>(), back_inserter(intVec));
    copy(istream_iterator<int>(cin), istream_iterator<int>(), back_insert_iterator< vector<int> >(intVec));

    copy(intVec.begin(), intVec.end(), ostream_iterator<int>(cout, " "));

    return 0;
}
