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
        DEBUG('t',"add new item to DLList key %d\n",sortKey);

        l->SortedInsert(itemPtr,sortKey);
    }
}


void removeNitem(int n,DLList *l)
{
    DEBUG('t',"Start removeNitem\n");

    for(int i=0;i<n;i++)
    {
        DEBUG('t',"i = %d\n",i);
        l->Remove(NULL);
    }

    DEBUG('t',"removeNitem finish!\n");
}
