#include <iostream>

using namespace std;

/** AUTO
    The auto keyword deduces the type of a declared variable from its initialization expression.
    auto declarator initializer;
*/

/** VOLATILE
    The volatile keyword is a type qualifier used to declare that an object can be modified
    in the program by something such as the operating system, the hardware, or a concurrently executing thread.
    volatile declarator;

    Такие переменные не оптимизируются, поскольку их значение может быть изменено извне.
    Объекты имеют атомарные свойства и могут быть использованы для locks/releases памяти в многопоточных приложениях.

    Volatile совместно с указателями говорят о том, что пользовательскому коду запрещено модифицировать объект,
    однако он может быть изменен извне. При этом, память каждый раз считывается.
*/

/** REGISTER
    The register keyword specifies that the variable is to be stored in a machine register, if possible.
*/

int main()
{
    auto int x; /// auto поменяет смысл в C++0x, убрать по совету Саттера

    volatile int v;

/// volatile + pointers

    volatile char* vpch;
    char* volatile pchv;

/// register
    register int var;

    return 0;
}
