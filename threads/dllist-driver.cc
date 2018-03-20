#include "dllist.h"
#include "utility.h"
#include "copyright.h"
#include "system.h"

void addNRandom(int n,DLList *l)
{
    int randomArray[10] = {33,22,11,44,55,66,77,88,99,5};
    for(int i=0;i<n;i++)
    {
        int sortKey = randomArray[i];
        void *itemPtr = (void*)new int(sortKey);
        printf("add new item to DLList key %d\n",sortKey);

        l->SortedInsert(itemPtr,sortKey);
    }
}


void removeNitem(int n,DLList *l)
{
    printf("start removeNitem\n");

    for(int i=0;i<n;i++)
    {
        printf("i = %d\n",i);
        l->Remove(NULL);
    }

    printf("removeNitem finish!\n");
}
