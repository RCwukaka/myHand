#ifndef __QUEUE_H
#define __QUEUE_H
//#define Queue_test

#include "public.h"

#define DataType void
static const u8 QMaxSize = 128;

class Queue
{

public:
    Queue();
    DataType *QGetFront(void);
    u8 QInsertRear(DataType *pItem);
    void QClearAll(void);

    u8 QLength();
    u8 QEmpty();
    u8 QFull();

private:
    u8 front;
    u8 rear;
    u8 count;
    DataType *qlist[QMaxSize];
    pthread_mutex_t qLock;
    pthread_cond_t qNotEmpty;
};

#endif
