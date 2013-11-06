#include <iostream>

using namespace std;

/// Function template
template <typename T>
T tmax(T x, T y)
{
    return (x > y) ? x : y;
}

class Cents
{
private:
    int m_nCents;
public:
    Cents(int nCents)
        : m_nCents(nCents)
    {
    }

     friend bool operator>(const Cents& c1, const Cents& c2);
};

bool operator>(const Cents& c1, const Cents& c2)
{
    return (c1.m_nCents > c2.m_nCents) ? true: false;
}

int main()
{
    /// Пример использование классов в качестве шаблонных параметров
    Cents cNickle(5);
	Cents cDime(10);
	/// Function template Instance
	Cents cBigger = tmax(cNickle, cDime);
    return 0;
}
