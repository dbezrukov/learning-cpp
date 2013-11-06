#include <iostream>

using namespace std;

/// When an enumerator is used, its value is implicitly converted to an integer when needed.

enum Enum
{
    one = 1,
    two = 2
};

int main()
{
    // compiles without any errors
    int x = one;
    cout << "x=" << x << endl;

    // without any errors
    Enum myEnum;
    myEnum = static_cast<Enum>(1);
    cout << "myEnum=" << myEnum << endl;

    return 0;
}
