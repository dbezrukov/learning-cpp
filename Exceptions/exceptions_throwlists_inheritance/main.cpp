#include <iostream>

using namespace std;

class Foo
{
public:
    void virtual abc() throw(int, double, long);
};

class Bar : public Foo
{
public:
    /// виртуальный метод нельзя переопределять по значению, обычный можно
    /// int abc() throw(int, double, long);

    void abc() throw(double, int, long); // ok

};

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
