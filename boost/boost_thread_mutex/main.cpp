#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include <iostream>
using namespace std;

/// для синхронизации iostream
boost::mutex io_mutex; // The iostreams are not guaranteed to be thread-safe!

class counter
{
public:
    counter() : count(0) { }

    /// сериализуем доступ к методу из нескольких потоков
    int increment()
    {
        boost::mutex::scoped_lock scoped_lock(mutex);
        return ++count;
    }

private:
    /// мьютекс для объекта counter
    boost::mutex mutex;
    int count;
};

counter c;

void change_count()
{
    int i = c.increment();
    /// только один поток может взадеть io_mutex
    boost::mutex::scoped_lock scoped_lock(io_mutex);
    std::cout << "count = " << i << std::endl;
}

int main()
{
    const int num_threads = 4;
    boost::thread_group thrds;

    /// создаем потоки
    for (int i=0; i < num_threads; ++i)
        thrds.create_thread(&change_count);

    /// ждем завершения
    thrds.join_all();

    return 0;
}
