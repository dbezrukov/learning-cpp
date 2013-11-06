// remove_copy_if example
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
using namespace std;

int main ()
{
  int srcVec[] = {1,2,5,3,4,5,6,7,8,9,5};
  vector<int> dstVec(11);

  cout << "srcVec contains:";
  copy(srcVec, srcVec+9, ostream_iterator<int>(cout, " "));

  cout << endl << "remove_copy(5)";
  vector<int>::iterator dstEnd = remove_copy(srcVec, srcVec+11, dstVec.begin(), 5);

  cout << endl << "srcVec contains:";
  copy(srcVec, srcVec+11, ostream_iterator<int>(cout, " "));

  cout << endl << "dstVec contains:";
  copy(dstVec.begin(), dstEnd, ostream_iterator<int>(cout, " "));

  ///

  return 0;
}
