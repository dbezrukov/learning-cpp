#include <iostream>

using namespace std;

class MyClass
{
public:
   MyClass(void) {}
   virtual ~MyClass() {}
   operator int() const { return (0); }
};

int main()
{
    MyClass myclass1, myclass2;
    myclass1=myclass2;
    return 0;
}
