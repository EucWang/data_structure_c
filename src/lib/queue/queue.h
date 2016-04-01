#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include <stdlib.h>

#include "../list/list.h"

typedef List Queue_my;

#define queue_m_init list_init
#define queue_m_destroy list_destroy

int queue_enqueue(Queue_my *pQueue, const void *data);
int queue_dequeue(Queue_my *pQueue, void **data);

#define queue_peek(mQueue) ((mQueue)->head == NULL ? NULL : (mQueue)->head->data)

#define queue_size list_size

#endif // QUEUE_H_INCLUDED
