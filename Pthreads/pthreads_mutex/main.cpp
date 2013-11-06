/**
    Синхронизация вывода в консоль несколькими потоками
*/
#include <iostream>
#include <sstream>
#include <pthread.h>

#define NTHREADS 2

using namespace std;

pthread_mutex_t mx = PTHREAD_MUTEX_INITIALIZER;

void* thread_function(void* message)
{
    int nThread = *(reinterpret_cast<int*>(message));
    int i=0;
    for (; i<100; i++)
    {
        pthread_mutex_lock( &mx );
        cout << "Thread" << nThread << " : " << i << endl;
        pthread_mutex_unlock( &mx );
    }
    pthread_exit(0);
}

int main()
{
    pthread_t thread_id[NTHREADS];

    for(int i=0; i < NTHREADS; i++)
    {
        int* nThread = new int;
        *nThread = i;
        pthread_create( &thread_id[i], NULL, thread_function, reinterpret_cast<void*>(nThread) );
    }

    for(int j=0; j < NTHREADS; j++)
    {
        pthread_join( thread_id[j], NULL);
    }
    return 0;
}
