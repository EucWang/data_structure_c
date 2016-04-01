#ifndef SET_COVER_H_INCLUDED
#define SET_COVER_H_INCLUDED

#include "../set/set.h"
#include <string.h>

typedef struct KSet_{
    void *key;
    Set pSet;
}KSet;

int kset_cover(Set *members, Set *subsets, Set *covering);

KSet *kset_get_init(char *key, Set *s);
int kset_match(KSet *kset1, KSet *kset2);
void kset_destroy(KSet *kset);

#endif // SET_COVER_H_INCLUDED
