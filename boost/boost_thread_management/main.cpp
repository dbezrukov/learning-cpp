#include <iostream>
#include <boost/thread.hpp>
#include <boost/date_time.hpp>

/// Simple function

void workerFunc(const char* msg)
{
    boost::posix_time::seconds workTime(3);

    std::cout << "Worker: running " << msg << std::endl;

    // Pretend to do something useful...
    boost::this_thread::sleep(workTime);

    std::cout << "Worker: finished" << std::endl;
}

int main(int argc, char* argv[])
{
    std::cout << "main: startup" << std::endl;

    /// запускаем поток, можно передать параметры
    boost::thread workerThread(workerFunc, "Deep thoughts");

    std::cout << "main: waiting for thread" << std::endl;

    /// говорим main ожидать завершения workerThread
    workerThread.join();

    std::cout << "main: done" << std::endl;

    return 0;
}
