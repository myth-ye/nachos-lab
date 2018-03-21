#include "dllist.h"
#include "utility.h"
#include "copyright.h"
#include "system.h"
#include "time.h"
void addNRandom(int n,DLList *l)
{
    DEBUG('t',"now start to add %d numbers\n",n);

    for(int i=0;i<n;i++)
    {
        int sortKey = Random()%100;
        void *itemPtr = (void*)new int(sortKey);
        DEBUG('t',"add new item to DLList key %d\n",sortKey);

        l->SortedInsert(itemPtr,sortKey);
    }
}


void removeNitem(int n,DLList *l)
{
    DEBUG('t',"Start removeNitem from head\n");

    for(int i=0;i<n;i++)
    {
        int keynum;
        keynum = *(int *)(l->Remove(NULL));
        DEBUG('t',"\t (i = %d,delete item key=%d)\n",i,keynum);
    }

    DEBUG('t',"removeNitem finish!\n");
}
