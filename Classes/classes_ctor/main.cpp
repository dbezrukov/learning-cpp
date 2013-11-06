#include <iostream>

using namespace std;

/** Обычные методы нельзя перегружать const-параметрами
    А конструкторы можно.
    Конструкторы копирования по умолчанию принимают const-ссылку
*/
class Foo
{
public:
    Foo()
    {
        cout << "std ctor" << endl;
    }
    Foo(Foo& src) /// -уже переопределяет стандартный конструктор копирования!
    {
        cout << "copy ctor" << endl;
    }
    Foo(const Foo& src)
    {
        cout << "const copy ctor" << endl;
    }
};



int main()
{
    Foo a;
    Foo b(a); /// Для const -объекта будет вызван const-версия конструктора
    return 0;
}
