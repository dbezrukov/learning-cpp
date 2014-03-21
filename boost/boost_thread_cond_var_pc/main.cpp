#include <iostream>
#include <vector>
#include <boost/utility.hpp>
#include <boost/thread/condition.hpp>
#include <boost/thread/thread.hpp>

using namespace std;

/// объектно-ориентированный вариант

class buffer : private boost::noncopyable
{
public:
    buffer(int n) : begin(0), end(0), buffered(0), circular_buf(n) { }

    void put(int m)
    {
        boost::mutex::scoped_lock lk(monitor);
        while ( buffered == circular_buf.size() )
        {
            buffer_not_full.wait(lk);
        }
        circular_buf[end] = m;
        end = (end+1) % circular_buf.size();
        ++buffered;
        buffer_not_empty.notify_one();
    }
    int remove()
    {
        boost::mutex::scoped_lock lk(monitor);
        while ( buffered == 0 )
        {
            buffer_not_empty.wait(lk);
        }
        int i = circular_buf[begin];
        begin = (begin+1) % circular_buf.size();
        --buffered;
        buffer_not_full.notify_one();
        return i;
    }

private:
    int begin, end, buffered;
    std::vector<int> circular_buf;
    boost::condition_variable buffer_not_full, buffer_not_empty;
    boost::mutex monitor;
};

buffer buf(5);
boost::mutex io_mutex;

void producer()
{
    int n = 0;
    while (n < 10000)
    {
        boost::this_thread::sleep( boost::posix_time::seconds(1) );
        buf.put(n);

        boost::mutex::scoped_lock io_lock(io_mutex);
        std::cout << "produce: " << n << std::endl;

        ++n;
    }
    buf.put(-1);
}

void consumer()
{
    int n;
    do
    {
        n = buf.remove();

        boost::mutex::scoped_lock io_lock(io_mutex);
        std::cout << "thread_id" << boost::this_thread::get_id() << ", consume: " << n << std::endl;
    } while (n != -1);
}

int main()
{
    boost::thread thrd1(&producer);

    boost::thread thrd2(&consumer);
    boost::thread thrd3(&consumer); /// можно добавить

    thrd1.join();
    thrd2.join();
    thrd3.join();

    return 0;
}
