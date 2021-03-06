#include <boost/thread/recursive_mutex.hpp>
#include <boost/thread/thread.hpp>
#include <iostream>

class counter
{
public:
    counter() : count(0) { }

    int add(int val)
    {
        boost::recursive_mutex::scoped_lock scoped_lock(mutex);
        count += val;
        return count;
    }
    int increment()
    {
        boost::recursive_mutex::scoped_lock scoped_lock(mutex);
        /// ����������� deadlock!!!
        return add(1);
    }
private:
    boost::recursive_mutex mutex;
    int count;
};

counter c;

void change_count()
{
    std::cout << "count = " << c.increment() << std::endl;
}

int main()
{
    const int num_threads=4;

    boost::thread_group threads;
    for (int i=0; i < num_threads; ++i)
        threads.create_thread(&change_count);

    threads.join_all();
    return 0;
}
