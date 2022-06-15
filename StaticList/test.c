#include <stdio.h>
#include "staticlist.h"

int main()
{
    StaticList list;
    int num, num2, num3;
    
    staticlist_init(&list);

    num = 1;
    num2 = 2;
    num3 = 3;
    staticlist_push(&list, &num);
    staticlist_push(&list, &num2);
    staticlist_push(&list, &num3);
    
    printf("%i\n", *((int *) staticlist_get(&list, 2)));
    
    return 0;
}
