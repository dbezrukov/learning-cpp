#include <iostream>
#include <queue>
#include <boost/thread/condition.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>

using namespace std;

/// Synch buffer
class buffer : private boost::noncopyable
{
public:
    buffer(int max_size = -1 )
        : maxSize ( max_size ) {}

    void put(int data)
    {
        boost::mutex::scoped_lock lock(monitor);
        while ( dataQueue.size() == maxSize )
        {
            buffer_not_full.wait(lock);
        }
        dataQueue.push(data);
        buffer_not_empty.notify_one();
    }
    int remove()
    {
        boost::mutex::scoped_lock lock(monitor);
        while ( dataQueue.empty() )
        {
            buffer_not_empty.wait(lock);
        }
        int temp = dataQueue.front();
        dataQueue.pop();
        buffer_not_full.notify_one();
        return temp;
    }
protected:
    int maxSize;
    std::queue<int> dataQueue; /// O(1) быстрее чем вектор O(N)
    boost::condition_variable buffer_not_full, buffer_not_empty;
    boost::mutex monitor;
};

buffer buf(10);

void producer()
{
    for (int n = 0; n < 100; ++n)
    {
        boost::this_thread::sleep( boost::posix_time::seconds(1) );
        buf.put(n);
    }
    buf.put(-1);
}

void consumer()
{
    int n;
    do
    {
        n = buf.remove();
    } while (n != -1);
}

int main()
{
    boost::thread thrd1(&producer);
    boost::thread thrd2(&consumer);

    thrd1.join();
    thrd2.join();

    return 0;
}
