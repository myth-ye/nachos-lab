#include "dllist.h"
#include "utility.h"
#include "copyright.h"
#include "system.h"
#include "time.h"
void addNRandom(int n,DLList *l)
{
    printf("now start to add %d numbers\n",n);
    for(int i=0;i<n;i++)
    {
        int sortKey = Random()%100;
        void *itemPtr = (void*)new int(sortKey);
        l->SortedInsert(itemPtr,sortKey);
    }
}


void removeNitem(int n,DLList *l)
{
    printf("Start remove %d item from head\n",n);
    for(int i=0;i<n;i++)
    {
        printf("delete No.%d=",i);
        l->Remove(NULL);
    }
    printf("removeNitem finish!\n");
}
