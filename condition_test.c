#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
void *thread1(void *);
void *thread2(void *);
int i = 1;
int main(void)
{
    pthread_t t_a;
    pthread_t t_b;
    pthread_create(&t_a, NULL, thread1, (void *)NULL);
    pthread_create(&t_b, NULL, thread2, (void *)NULL);
    pthread_join(t_b, NULL);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    exit(0);
}
void *thread1(void *junk)
{
    for(i = 1; i <= 9; i++)
    {
        printf("thread1 get mutex lock...\n");
        pthread_mutex_lock(&mutex);
        printf("thread1 get mutex lock OK!\n");
        //if(i%3==0)
        //else
        //printf("thead1:%d\n",i);*/
        //while(1)
        //pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
        printf("thread1 release mutex lock\n");
        usleep(50);
    }
}
void *thread2(void *junk)
{
    while(i < 9)
    {
        printf("thread2 get mutex lock...\n");
        pthread_mutex_lock(&mutex);
        printf("thread2 get mutex lock OK!\n");
        //if(i%3!=0)
        pthread_cond_wait(&cond, &mutex);
        while(1) sleep(10);
        //printf("thread2:%d\n",i);*/
        pthread_mutex_unlock(&mutex);
        printf("thread2 release mutex lock\n");
        usleep(50);
    }
}
