/*栈 自定义实现*/

#include <stdlib.h>
#include "../list/list.h"
#include "stack.h"


int stack_push(Stack *pStack, const void *data){
    return list_ins_next(pStack, NULL, data);
}

int stack_pop(Stack *pStack, void **data){
    return list_rem_next(pStack, NULL, data);
}
