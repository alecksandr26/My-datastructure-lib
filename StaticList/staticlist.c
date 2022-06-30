#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "staticlist_p.h"

/* staticlist_remove_index: To remove data by index from the list return "0" if sucessfull else ortherwise */
int staticlist_remove_index(StaticList *list, unsigned index)
{
    if (list->size <= index)
        return -1;
    
    for ( ; index < list->size - 1; ++index)
        list->list[index] = list->list[index + 1];
    
    list->size--;
    return 0;
}

/* staticlist_remove_data: To remove data from the list return "0" if sucessfull else ortherwise */
int staticlist_remove_data(StaticList *list, void *data)
{
    unsigned index;
    
    for (index = 0; index < list->size; ++index)
        if (list->list[index] == data)
            break;

    for ( ; index < list->size - 1; ++index)
        list->list[index] = list->list[index + 1];

    list->size--;
    return 0;
}


/* realloc_list: Reacllo all the memory return "0" if sucessfull else otherwise it is a private method */
static int realloc_list(StaticList *list)
{
    list->max_size *= 2;
    if ((list->list = (void **) realloc(list->list, sizeof(void *) * list->max_size)) == NULL)
        return -1;

    return 0;
}


/* staticlist_insert: Insert an element by index return "0" if successful else return otherwise */
int staticlist_insert(StaticList *list, unsigned index, void *data)
{
    void *temp;
    
    if (index >= list->size)
        return -1;

    if (++(list->size) == list->max_size)
        if (realloc_list(list) != 0)
            return -1;

    for (temp = NULL; index < list->size; ++index) {
        temp = list->list[index];
        list->list[index] = data;
        data = temp;
    }
    
    return 0;
}

/* staticlist_get: Return the data from an index */
void *staticlist_get(StaticList *list, unsigned index)
{
    if (list->size <= index)
        return NULL;

    return list->list[index];
}

/* staticlist_push: To push to the list an element return "0" if sucessfull else return otherwire */
int staticlist_push(StaticList *list, void *data)
{
    if (++(list->size) == list->max_size)
        if (realloc_list(list) != 0)
            return -1;
                
    list->list[list->size - 1] = data;
    return 0;
}

/* create_staticlist: Create a new instance of the list */
StaticList *create_staticlist()
{
    StaticList *list;

    if ((list = (StaticList *) malloc(sizeof(StaticList))) == NULL) {
        fprintf(stderr, "Error: Not enough memory for a new instance of StaticList\n");
        exit(EXIT_FAILURE);
    }
    
    list->size = 0;
    list->max_size = INITIAL_MAX_SPACE;
    if ((list->list =  malloc(sizeof(void *) * list->max_size)) == NULL) {
        fprintf(stderr, "Error: Not enough memory for a new instance of StaticList\n");
        exit(EXIT_FAILURE);
    }

    return list;
}


/* destroy_staticlist: To destroy completly a list */
void destroy_staticlist(StaticList *list)
{
    free(list->list);
    free(list);
}
