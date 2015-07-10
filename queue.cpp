#include "queue.h"

Queue::Queue()
{
    front = 0;
    rear = 0;
    count = 0;
    pthread_mutex_init(&qLock, NULL);
    pthread_cond_init(&qNotEmpty, NULL);
}
u8 Queue::QInsertRear(DataType *pItem)
{
    if(QMaxSize == count)
    {
        printf("Queue overflow!\n");
        return FALSE;
    }
    pthread_mutex_lock(&qLock);
    //printf("QInsertRear\n");
    count++;
    qlist[rear] = pItem;
    rear  = (rear + 1) % QMaxSize;

    pthread_cond_signal(&qNotEmpty);
    pthread_mutex_unlock(&qLock);
    return TRUE;
}
DataType *Queue::QGetFront(void)
{
    struct timespec timeout;
    struct timeval now;
    uint dwMilliseconds;
    int ret;
    DataType *pItem;
    //printf("QGetFront get lock...\n");
    pthread_mutex_lock(&qLock);
    //printf("QGetFront get lock ok!\n");
    if(0 == count)
    {
        gettimeofday(&now, NULL);
        dwMilliseconds = 500;
        timeout.tv_sec = now.tv_sec + dwMilliseconds / 1000;
        timeout.tv_nsec = now.tv_usec * 1000 + (dwMilliseconds % 1000) * 1000000;
        //timeout.tv_sec = time(0) + 1;
        //timeout.tv_nsec = 0;
        ret = pthread_cond_timedwait(&qNotEmpty, &qLock, &timeout);
        if((ret == ETIMEDOUT) && (0 == count))
        {
            pthread_mutex_unlock(&qLock);
            return NULL;
        }
    }
    pItem = qlist[front];
    //printf("QGetFront a item OK!\n");
    count--;
    qlist[front] = NULL;
    front  = (front + 1) % QMaxSize;
    pthread_mutex_unlock(&qLock);
    //printf("QGetFront release lock ok!\n");
    return pItem;
}
void Queue::QClearAll(void)
{
    printf("QClearAll not implement\n");
}

u8 Queue::QLength()
{
    printf("QLength not implement\n");
    return FALSE;
}
u8 Queue::QEmpty()
{
    printf("QEmpty not implement\n");
    return FALSE;
}
u8 Queue::QFull()
{
    printf("QFull not implement\n");
    return FALSE;
}

#ifdef Queue_test

RXPacket packet_temp;

void *consumer(void *pData)
{
    Queue *pObj = (Queue *)pData;
    RXPacket *pPacket;
    while(1)
    {
        pPacket = (RXPacket *)pObj->QGetFront();
        if(pPacket != NULL)
        {
            printf("read item. addr:%d\t synHead:%d\n", pPacket->addr, pPacket->synHead);
            free(pPacket);
        }
        //usleep(1);
    }
    return NULL;
}
void *producer(void *pData)
{
    int times = 0;
    Queue *pObj = (Queue *)pData;
    RXPacket *pPacket;
    while(1)
    {
        pPacket = (RXPacket *)malloc(sizeof(RXPacket));
        if(pPacket == NULL)
        {
            printf("malloc memery error!\n");
            exit(1);
        }
        else
        {
            memcpy(pPacket, &packet_temp, sizeof(RXPacket));
            pPacket->addr = times;
            pPacket->synHead = rand() % 100;
            printf("write item. addr:%d\t synHead:%d\n", pPacket->addr, pPacket->synHead);
            pObj->QInsertRear(pPacket);
        }
        times++;
        msleep((rand() % (1000 - 100)) + 100);
    }
    return NULL;
}

int main(int argc, char **argv)
{
    u8 i;
    Queue queue_test;
    RXPacket *pPacket;
    u8 rxdata1 = 0x23;
    packet_temp.synHead = 0x66;
    packet_temp.addr = 0;
    packet_temp.pData = &rxdata1;
    packet_temp.synRear = 0x88;
    srand((unsigned int)time(0));

    int error;
    pthread_t consumerThread;
    pthread_t producerThread;
    error = pthread_create(&consumerThread, NULL, consumer, &queue_test);
    if(error != 0)
    {
        printf("readThread not created\n");
        //exit(1);
    }
    error = pthread_create(&producerThread, NULL, producer, &queue_test);
    if(error != 0)
    {
        printf("readThread not created\n");
        //exit(1);
    }
    pthread_join(consumerThread, NULL);
    pthread_join(producerThread, NULL);

    while(1)
    {
        sleep(100);
    }
    /*
    printf("write 80 item to queue==========================================\n");
    for(i=1; i<81; i++)
    {
        pPacket = (RXPacket*)malloc(sizeof(RXPacket));
        if(pPacket==NULL)
        {
            printf("malloc memery error!\n");
            exit(1);
        }
        else
        {
            memcpy(pPacket, &packet_temp, sizeof(RXPacket));
            pPacket->addr = i;
            pPacket->synHead = (u8)(32.0*rand()/(RAND_MAX+1.0));
            printf("packet addr:%d\t synHead:%d\n", pPacket->addr, pPacket->synHead);
            queue_test.QInsertRear(pPacket);
        }
    }
    printf("read 60 item form queue=========================================\n");
    for(i=0; i<60; i++)
    {
        pPacket = queue_test.QGetFront();
        if(pPacket!=NULL)
        {
            printf("packet addr:%d\t synHead:%d\n", pPacket->addr, pPacket->synHead);
            free(pPacket);
        }
    }
    printf("write 100 item to queue again===================================\n");
    for(i=200; i>100; i--)
    {
        pPacket = (RXPacket*)malloc(sizeof(RXPacket));
        if(pPacket==NULL)
        {
            printf("malloc memery error!\n");
            exit(1);
        }
        else
        {
            memcpy(pPacket, &packet_temp, sizeof(RXPacket));
            pPacket->addr = i;
            pPacket->synHead = (u8)(32.0*rand()/(RAND_MAX+1.0));
            printf("packet addr:%d\t synHead:%d\n", pPacket->addr, pPacket->synHead);
            queue_test.QInsertRear(pPacket);
        }
    }
    printf("read all item form queue =======================================\n");
    for(i=0; i<QMaxSize; i++)
    {
        pPacket = queue_test.QGetFront();
        if(pPacket!=NULL)
        {
            printf("packet addr:%d\t synHead:%d\n", pPacket->addr, pPacket->synHead);
            free(pPacket);
        }
    }*/
    return 0;
}
#endif


