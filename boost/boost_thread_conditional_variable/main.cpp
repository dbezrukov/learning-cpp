#include <boost\thread\thread.hpp>
#include <boost\thread\mutex.hpp>
#include <boost\thread\condition.hpp>  ///!!!!!! boost\thread\!!!!!!
#include <queue>

class Buffer
{
public:
    Buffer(int max_size = -1)
        : maxSize( max_size ) {}
    void put(int n)
    {
        boost::mutex::scoped_lock lock(monitor);
        while ( dataQueue.size() == maxSize )
        {
            buffer_not_full.wait( lock );
        }
        dataQueue.push(n);
        buffer_not_empty.notify_one();
    }
    int remove()
    {
        boost::mutex::scoped_lock lock(monitor);
        while ( dataQueue.empty() )
        {
            buffer_not_empty.wait( lock );
        }
        int temp = dataQueue.front();
        dataQueue.pop();
        buffer_not_full.notify_one();
        return temp;
    }
protected:
    int maxSize;
    std::queue<int> dataQueue;     ///         queue<int>   !!!!!!!!!!!!
    boost::condition buffer_not_full, buffer_not_empty;
    boost::mutex monitor;
};

Buffer buffer(5);

void producer()
{
    for (int n=0; n<100; ++n)
    {
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
    } while( n != -1 );
    buf.put(-1);
}

int main()
{
    boost::thread producer_thread(&producer);
    boost::thread consumer_thread(&consumer);
    producer_thread.join();
    consumer_thread.join();
    return 0;
}
















































/*
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp> /// condition.hpp
#include <queue>
#include <iostream>

class buffer : private boost::noncopyable
{
public:
    buffer(int max_size = -1) : maxSize(max_size) {}
    void put(int n)
    {
        boost::mutex::scoped_lock lock(monitor); /// без амперсанда
        while ( dataQueue.size() == maxSize )
        {
            buffer_not_full.wait(lock);
        }
        dataQueue.push(n);
        buffer_not_empty.notify_one();
    }
    int remove()
    {
        boost::mutex::scoped_lock lock(monitor);
        while ( dataQueue.empty() ) /// empty()
        {
            buffer_not_empty.wait(lock);
        }
        int temp = dataQueue.front();
        dataQueue.pop();
        buffer_not_full.notify_one();
        return temp;
    }
protected:
    std::queue<int> dataQueue;
    int maxSize;
    boost::mutex monitor;
    boost::condition buffer_not_full, buffer_not_empty; /// boost_condition
};

buffer buf; /// buffer
boost::mutex io_mutex;

void producer()
{
    for (int n=0; n<100; n++)
    {
        boost::this_thread::sleep( boost::posix_time::seconds(1) );
        buf.put(n);

        boost::mutex::scoped_lock lock(io_mutex); /// scoped lock
        std::cout << "produced " << n << std::endl;
    }
    buf.put(-1);
}

void consumer()
{
    int n;
    do
    {
        n = buf.remove();

        boost::mutex::scoped_lock lock(io_mutex);
        std::cout << "consumed " << n << std::endl;
    } while ( n!= -1 );
    buf.put(-1);
}

int main()
{
    boost::thread producer_thread(&producer);
    boost::thread consumer_thread(&consumer);

    producer_thread.join();
    consumer_thread.join();
}





















/*#include <iostream>
#include <boost/thread/condition.hpp>
#include <boost/thread/thread.hpp>

using namespace std;

boost::condition_variable buffer_not_full, buffer_not_empty;
boost::mutex monitor;

struct buffer
{
    buffer()
        : max_size( 5 )
        , buffered( 0 )
    {
    }
    void put()
    {
        cout << "put" << endl;
        ++buffered;
    };
    void remove()
    {
        cout << "remove" << endl;
        --buffered;
    };
    int max_size;
    int buffered;
};

buffer buf;

void producer()
{
    while( true )
    {
        boost::this_thread::sleep( boost::posix_time::seconds(1) );
        boost::mutex::scoped_lock lock(monitor);
        while ( buf.buffered == buf.max_size )
        {
            buffer_not_full.wait( lock );
        }
        buf.put();
        ++buf.buffered;
        buffer_not_empty.notify_one();
    }
}

void consumer()
{
    while ( true )
    {
        boost::mutex::scoped_lock lock(monitor);
        while( buf.buffered == 0 )
        {
            buffer_not_empty.wait(lock);
        }
        buf.remove();
        --buf.buffered;
        buffer_not_full.notify_one();
    }
}

int main()
{
    boost::thread thrd1(&producer);

    boost::thread thrd2(&consumer);
    boost::thread thrd3(&consumer); /// можно добавить

    thrd1.join();
    thrd2.join();
    thrd3.join();
}
*/
