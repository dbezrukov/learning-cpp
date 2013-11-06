/**
    Синхронизация вывода в консоль несколькими потоками
*/
#include <iostream>
#include <sstream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NTHREADS 2

using namespace std;
sem_t full, empty;

int data;

void* thread_producer(void*)
{
    for (int i=1;;i++)
    {
        usleep( 100000 );
        sem_wait( &full );
        data = i;
        sem_post( &empty );
    }
    pthread_exit(0);
}

void* thread_consumer(void*)
{
    while (1)
    {
        int t;
        sem_wait( &empty );
        t = data;
        sem_post( &full );
        cout << t << endl;
    }
    pthread_exit(0);
}

int main()
{
    sem_init(&full,  0, 1);
    sem_init(&empty, 0, 0);

    pthread_t thread_producer_id, thread_consumer_id;

    pthread_create( &thread_producer_id, NULL, thread_producer, NULL );
    pthread_create( &thread_consumer_id, NULL, thread_consumer, NULL );

    pthread_join( thread_producer_id, NULL);
    pthread_join( thread_consumer_id, NULL);
    return 0;
}

