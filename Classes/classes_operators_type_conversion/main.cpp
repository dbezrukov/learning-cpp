#include <iostream>

using namespace std;

template<class T, class X>
class Obj
{
    T my_t;
    X my_x;
public:
    Obj(T t, X x)
        : my_t(t)
        , my_x(x)
    {
    }
    operator T() const
    {
        return my_t;
    };
};

int main()
{
    int iT;
    Obj<int, float> my_obj(1, 2.f);
    iT = my_obj;
    return 0;
}
