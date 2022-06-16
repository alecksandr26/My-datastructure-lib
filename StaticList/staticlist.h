#ifndef __STATIC_LIST_H__
#define __STATIC_LIST_H__

#include <stdlib.h>

#define INITIAL_MAX_SPACE 2

/* Data structure */
typedef struct _StaticList{
    unsigned size;
    unsigned max_size;
    void **list;
} StaticList;

/* staticlist_remove: To remove data from the list return "0" if sucessfull else ortherwise */
#define staticlist_remove(list, element_or_index) _Generic((element_or_index), \
                                                           unsigned : staticlist_remove_index(list, element_or_index), \
                                                           void *: staticlist_remove_data(list, element_or_index), \
                                                           int : staticlist_remove_index(list, element_or_index), \
                                                           long : staticlist_remove_index(list, element_or_index))

/* staticlist_insert: Insert an element by index return "0" if successful else return otherwise */
int staticlist_insert(StaticList *list, unsigned index, void *data);   

/* staticlist_get: Return the data from an index */
void *staticlist_get(StaticList *list, unsigned index);

/* staticlist_push: To push to the list an element return "0" if sucessfull else return otherwire */
int staticlist_push(StaticList *list, void *data);

/* staticlist_init: Initialize the list */
void staticlist_init(StaticList *list);

/* staticlist_destroy: To destroy completly a list */
void staticlist_destroy(StaticList *list);

/* staticlist_size: Returns the size of the list */
#define staticlist_size(list) ((list)->size)

#endif
