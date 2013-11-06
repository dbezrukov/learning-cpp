#include <iostream>
#include <queue>
#include <string>

using namespace std;

class Foo
{
public:
    friend bool operator<(const Foo& lhs, const Foo& rhs);
    friend ostream& operator<<(ostream& ostr, const Foo& rhs);

    Foo(int intVal)
        : _intVal( intVal )
    {
    }
protected:
    int _intVal;
};

bool operator<(const Foo& lhs, const Foo& rhs)
{
    return ( lhs._intVal < rhs._intVal );
}

ostream& operator<<(ostream& ostr, const Foo& rhs)
{
    ostr << rhs._intVal;
}

template <typename T>
void printQueue(string name, priority_queue<T> pqueue)
{
    cout << name << ": ";
    while ( !pqueue.empty() )
    {
        T tmp = pqueue.top();
        cout << tmp << " ";
        pqueue.pop();
    }
    cout << endl;
}

int main()
{
    // Очередь с приоритетом. От большего к меньшему
    // Нет смысла переопределять станартный оператор <, лучше добавить в него больше логики.
    /*
    priority_queue<Foo> pqueue;
    pqueue.push( 4 );
    pqueue.push( 6 );
    pqueue.push( 6 );
    pqueue.push( 2 );

    printQueue("PQueue", pqueue);
    */


    priority_queue<int> pqueue;
    pqueue.push( 4 );
    pqueue.push( 6 );
    pqueue.push( 6 );
    pqueue.push( 2 );

    printQueue("PQueue", pqueue);

    return 0;
}
