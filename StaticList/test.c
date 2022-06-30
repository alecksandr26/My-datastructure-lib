#include <stdio.h>
#include <assert.h>
#include "staticlist.h"

int main()
{
    StaticList *list;
    int num, num2, num3, num4, num5;
    
    list = create_staticlist(NULL);

    num = 1;
    num2 = 2;
    num3 = 3;
    num4 = 4;
    num5 = 5;

    
    /* Run the tests */
    assert(staticlist_push(list, &num) == 0);
    assert(staticlist_push(list, &num2) == 0);
    assert(staticlist_push(list, &num3) == 0);
    assert(staticlist_push(list, &num4) == 0);
    assert(staticlist_push(list, &num5) == 0);
    
    assert(list->size == 5);

    assert(staticlist_delete(list, (void *) &num2) == 0);
    
    assert(staticlist_delete(list, 0) == 0);
    
    assert(*((int *) staticlist_get(list, list->size - 1)) == 5);
    assert(*((int *) staticlist_get(list, 0)) == 3);

    assert(destroy_staticlist(list) == 0);
    
    return 0;
}
