#ifndef __STATIC_LIST_P_H__
#define __STATIC_LIST_P_H__

#define INITIAL_MAX_SPACE 2

/* Data structure */
typedef struct static_list_t {
    unsigned size;
    void **list;
    unsigned max_size;
    int (*destroy_element)(void *element);
} StaticList;

/* staticlist_delete_index: To delete data by index from the list return "0" if sucessfull else ortherwise */
int staticlist_delete_index(StaticList *list, unsigned index);

/* staticlist_delete_data: To delete data from the list return "0" if sucessfull else ortherwise */
int staticlist_delete_data(StaticList *list, void *data);

/* staticlist_delete: To delete data from the list return "0" if sucessfull else ortherwise */
#define staticlist_delete(list, element_or_index) _Generic((element_or_index), \
                                                           void *: staticlist_delete_data, \
                                                           unsigned : staticlist_delete_index, \
                                                           int : staticlist_delete_index) (list, element_or_index)
                                                           

/* staticlist_insert: Insert an element by index return "0" if successful else return otherwise */
int staticlist_insert(StaticList *list, unsigned index, void *data);   

/* staticlist_get: Return the data from an index */
void *staticlist_get(StaticList *list, unsigned index);

/* staticlist_push: To push to the list an element return "0" if sucessfull else return otherwire */
int staticlist_push(StaticList *list, void *data);

/* staticlist_pop: Removed the last object and return it */
void *staticlist_pop(StaticList *list);

/* create_staticlist: Create a new instance of the list and return it
   destroy_element: A function to deallocate the memory of the objects returns 0 if okay else returns otherwise
 */
StaticList *create_staticlist(int (*destroy_element)(void *element));

/* destroy_staticlist: To destroy completly a list returns 0 if okay else otherwise */
int destroy_staticlist(StaticList *list);

/* staticlist_size: Returns the size of the list */
#define staticlist_size(list) ((list)->size)

#endif
