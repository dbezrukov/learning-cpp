#include <iostream>

using namespace std;

template<typename T>
class DynArray
{
    T* contents;
    int size;
public:
    /// explicit применяется только к конструкторам имеющим ровно один аргумент
    /// И позволяет предоствратить неявное преобразование с использованием
    /// данного конструктора
    explicit DynArray(int initial_size) {};
};

class Foo
{
public:
    Foo(int i) {};
};

int main()
{
    //DynArray<std::string> a(7);
    //DynArray<std::string> b('7');
    DynArray<std::string> c = DynArray<std::string>(7);
    //DynArray<std::string> d(a);
    //DynArray<std::string> e = b;

    return 0;
}
