#include <iostream>
#include <iterator>
#include <algorithm>
#include <queue>
#include <list>
using namespace std;

template <typename T>
class priority_stack
{
public:
    priority_stack() {};
    void put(int n)
    {
        pqueue.push(n);

        priority_queue<T> tmpqueue;
        while ( !pqueue.empty() )
        {
            tmpqueue.push( pqueue.top() );
            pqueue.pop();
        }
        while ( !tmpqueue.empty() )
        {
            pqueue.push( tmpqueue.top() );
            tmpqueue.pop();
        }
    }
    void pop()
    {
        pqueue.pop();
    }
    int top()
    {
        return pqueue.top();
    }
    bool empty()
    {
        return pqueue.empty();
    }
protected:
    priority_queue<T> pqueue;
};

int main ()
{
    priority_stack<int> pstack;
    pstack.put(6);
    pstack.put(3);
    pstack.put(4);
    pstack.put(5);
    pstack.put(2);

    while ( !pstack.empty() )
    {
        cout << pstack.top() << endl;
        pstack.pop();
    }
    return 0;
}
