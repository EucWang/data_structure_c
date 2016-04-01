#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdlib.h>
#include "../list/list.h"

/*Stack作为List的一个实现*/
typedef List Stack;

/*公共接口*/

#define stack_init list_init

#define stack_destroy list_destroy

int stack_push(Stack *pStack, const void *data);

int stack_pop(Stack *pStack, void **data);

#define stack_peek(pStack) ((pStack)->head == NULL?NULL:(pStack)->head->data)

#define stack_size list_size

#endif // STACK_H_INCLUDED
