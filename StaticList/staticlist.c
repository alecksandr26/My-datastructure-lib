#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "staticlist_p.h"

/* realloc_list: Reacllo all the memory return "0" if sucessfull else otherwise it is a private method */
static int realloc_list(StaticList *list)
{
    if ((list->list = (void **) realloc(list->list, sizeof(void *) * list->max_size)) == NULL)
        return -1;

    return 0;
}


/* staticlist_delete_index: To delete data by index from the list return "0" if sucessfull else ortherwise */
int staticlist_delete_index(StaticList *list, unsigned index)
{
    void *data;
    
    if (list == NULL || list->size <= index)
        return -1;

    /* First get the address of the element */
    data = list->list[index];

    /* Overwrite the array */
    for ( ; index < list->size - 1; ++index)
        list->list[index] = list->list[index + 1];
    

    /* If there is a needed fuc to delete the element */
    if (list->destroy_element != NULL)
        if (list->destroy_element(data) != 0)
            return -1;

    /* If it is needed reallocate the list */
    if (--(list->size) == (list->max_size / 2)) {
        list->max_size /= 2;
        if (realloc_list(list) != 0)
            return -1;
    }
    
    return 0;
}

/* staticlist_delete_data: To delete data from the list return "0" if sucessfull else ortherwise */
int staticlist_delete_data(StaticList *list, void *data)
{
    unsigned index;

    if (list == NULL)
        return -1;
    
    for (index = 0; index < list->size; ++index)
        if (list->list[index] == data)
            break;

    for ( ; index < list->size - 1; ++index)
        list->list[index] = list->list[index + 1];

    /* If there is a needed function to delete the item */
    if (list->destroy_element != NULL)
        if (list->destroy_element(data) != 0)
            return -1;

    /* If it is needed reallocate the list */
    if (--(list->size) == (list->max_size / 2)) {
        list->max_size /= 2;
        if (realloc_list(list) != 0)
            return -1;
    }
    
    return 0;
}


/* staticlist_insert: Insert an element by index return "0" if successful else return otherwise */
int staticlist_insert(StaticList *list, unsigned index, void *data)
{
    void *temp;
    
    if (list == NULL || index >= list->size)
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
    if (list == NULL || list->size <= index)
        return NULL;

    return list->list[index];
}

/* staticlist_push: To push to the list an element return "0" if sucessfull else return otherwire */
int staticlist_push(StaticList *list, void *data)
{
    if (list == NULL)
        return -1;
    
    if (++(list->size) == list->max_size) {
        list->max_size *= 2;
        if (realloc_list(list) != 0)
            return -1;
    }
                
    list->list[list->size - 1] = data;
    return 0;
}


/* staticlist_pop: Removed the last element and return it */
void *staticlist_pop(StaticList *list)
{
    void *data;
    
    if (list == NULL || list->size == 0)
        return NULL;

    /* Get the last element */
    data = list->list[list->size - 1];

    /* If it is needed reallocate the list */
    if (--(list->size) == (list->max_size / 2)) {
        list->max_size /= 2;
        if (realloc_list(list) != 0)
            return NULL;
    }
    
    return data;
}

/* create_staticlist: Create a new instance of the static list and return it */
StaticList *create_staticlist(int (*destroy_element)(void *element))
{
    StaticList *list;


    if ((list = (StaticList *) malloc(sizeof(StaticList))) == NULL) {
        fprintf(stderr, "Error: Not enough memory for a new instance of StaticList\n");
        exit(EXIT_FAILURE);
    }
    
    list->size = 0;
    list->max_size = INITIAL_MAX_SPACE;
    list->destroy_element = destroy_element;
    if ((list->list =  malloc(sizeof(void *) * list->max_size)) == NULL) {
        fprintf(stderr, "Error: Not enough memory for a new instance of StaticList\n");
        exit(EXIT_FAILURE);
    }

    return list;
}


/* destroy_staticlist: To destroy completly a list returns 0 if okay else otherwise */
int destroy_staticlist(StaticList *list)
{
    if (list == NULL)
        return -1;
    
    free(list->list);
    free(list);

    return 0;
}
