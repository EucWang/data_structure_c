#include <stdlib.h>

#include "../list/list.h"
#include "queue.h"


/*入列*/
int queue_enqueue(Queue_my *pQueue, const void *data){
    return list_ins_next(pQueue,list_tail(pQueue),data);
}

/*出列*/
int queue_dequeue(Queue_my *pQueue, void **data){
    return list_rem_next(pQueue, NULL, data);
}

