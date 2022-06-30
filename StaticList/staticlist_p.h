#ifndef __STATIC_LIST_P_H__
#define __STATIC_LIST_P_H__

#define INITIAL_MAX_SPACE 2

/* Data structure */
typedef struct static_list_t {
    unsigned size;
    void **list;
    unsigned max_size;
} StaticList;

/* staticlist_remove_index: To remove data by index from the list return "0" if sucessfull else ortherwise */
int staticlist_remove_index(StaticList *list, unsigned index);

/* staticlist_remove_data: To remove data from the list return "0" if sucessfull else ortherwise */
int staticlist_remove_data(StaticList *list, void *data);

/* staticlist_remove: To remove data from the list return "0" if sucessfull else ortherwise */
#define staticlist_remove(list, element_or_index) _Generic((element_or_index), \
                                                           void *: staticlist_remove_data, \
                                                           unsigned : staticlist_remove_index, \
                                                           int : staticlist_remove_index) (list, element_or_index)
                                                           

/* staticlist_insert: Insert an element by index return "0" if successful else return otherwise */
int staticlist_insert(StaticList *list, unsigned index, void *data);   

/* staticlist_get: Return the data from an index */
void *staticlist_get(StaticList *list, unsigned index);

/* staticlist_push: To push to the list an element return "0" if sucessfull else return otherwire */
int staticlist_push(StaticList *list, void *data);

/* create_staticlist: Create a new instance of the list */
StaticList *create_staticlist();

/* destroy_staticlist: To destroy completly a list */
void destroy_staticlist(StaticList *list);

/* staticlist_size: Returns the size of the list */
#define staticlist_size(list) ((list)->size)

#endif
