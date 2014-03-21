#include <iostream>
#include <boost/thread.hpp>

using namespace std;

/// Метод объекта выполняется в отдельном потоке

class Worker
{
public:

    Worker()
    {
        /// the thread is not-a-thread until we call start()
    }

    void start(int N)
    {
        m_Thread = boost::thread(&Worker::processQueue, this, N);
    }

    void join()
    {
        m_Thread.join();
    }

    void processQueue(unsigned N)
    {
        cout << "Worker: started, will work for " << N << "s" << endl;

        // We're busy, honest!
        boost::this_thread::sleep( boost::posix_time::seconds( N ) );

        cout << "Worker: completed" << endl;
    }
private:
    boost::thread m_Thread;
};

int main(int argc, char* argv[])
{
    cout << "main: startup" << endl;

    Worker worker;

    worker.start(3);

    cout << "main: waiting for thread" << endl;

    worker.join();

    cout << "main: done" << endl;

    return 0;
}
