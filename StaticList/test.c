#include <stdio.h>
#include <assert.h>
#include "staticlist.h"

int main()
{
    StaticList list;
    int num, num2, num3, num4, num5;
    
    staticlist_init(&list);

    num = 1;
    num2 = 2;
    num3 = 3;
    num4 = 4;
    num5 = 5;

    
    /* Run the tests */
    assert(staticlist_push(&list, &num) == 0);
    assert(staticlist_push(&list, &num2) == 0);
    assert(staticlist_push(&list, &num3) == 0);
    assert(staticlist_push(&list, &num4) == 0);
    assert(staticlist_push(&list, &num5) == 0);


    assert(staticlist_remove(&list, (void *) &num2) == 0);
    
    assert(staticlist_remove(&list, 0) == 0);
    
    assert(*((int *) staticlist_get(&list, staticlist_size(&list) - 1)) == 5);
    assert(*((int *) staticlist_get(&list, 0)) == 3);
    staticlist_destroy(&list);
                                                        
    
    return 0;
}
