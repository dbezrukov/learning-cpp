#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream ifs;
    ifs.open("test.txt");

    /// NOT GOOD - просто и понятно
    if (!ifs.good())
    {
        cout << "Couldn't open the file" << endl;
        return 1;
    }

    string temp;

    while (ifs >> temp)
    {
        cout << temp << endl;
    }
    return 0;
}
