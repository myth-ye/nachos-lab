#include "copyright.h"
#include "utility.h"
#include "dllist.h"
#include "system.h"

extern int errorNum;
//there are many ideas in list.cc to inspire!

DLLElement::DLLElement(void *itemPtr, int sortKey)
{
    prev = NULL;
    next = NULL;
    key = sortKey;
    item = itemPtr;
}

DLList::DLList()
{
    first = NULL;
    last = NULL;
    lock = new Lock("dllist_Lock");
}

DLList::~DLList()
{
    lock->Acquire();
    while(!IsEmpty())
        Remove(NULL);
    lock->Release();
    delete lock;
}

bool DLList::IsEmpty()
{
    if(first==NULL)
        return true;
    else
        return false;
}

void DLList::Prepend(void *item)
{
    lock->Acquire();
    if(IsEmpty())
    {
        DLLElement *e = new DLLElement(item,1);
        first = e;
        last = e;
    }
    else
    {
        DLLElement *e = new DLLElement(item,first->key-1);
        e->next = first;
        first->prev = e;
        first = e;
    }
    lock->Release();
}
void DLList::Append(void *item)
{
    lock->Acquire();
    if(IsEmpty())
    {
        DLLElement *e = new DLLElement(item,1);
        first = e;
        last = e;
    }
    else
    {
        DLLElement *e = new DLLElement(item,last->key+1);
        e->prev = last;
        last->next = e;
        last = e;
    }
    lock->Release();
}

void *DLList::Remove(int *keyPtr)
{
    lock->Acquire();


    DLLElement *e = first;
    void *itemPtr = NULL;

    if (IsEmpty())
    {
        printf("DLList is empty.\n");
        return NULL;
    }

    if (e == last)
    {
        first = NULL;
        if(errorNum==4)
        {
            //DEBUG('t',"Yield caused by error 4\n");
            printf("\n!!! Yield caused by error 4\n");
            currentThread->Yield();
        }
        last = NULL;
    }
    else
    {
        first = e->next;
        first->prev = NULL;
    }

    if(keyPtr != NULL)
        *keyPtr = e->key;
    itemPtr = e->item;

    delete e;


    printf("%.2d |",*(int *)itemPtr);
    for(DLLElement *tmp = first;
            tmp != NULL;tmp = tmp->next)
    {
        printf("%d ",tmp->key);
    }
    printf("\n");
    lock->Release();
    return itemPtr;
}

void DLList::SortedInsert(void *item, int sortKey)
{
    lock->Acquire();
    printf("add %.2d |",sortKey);
    DLLElement *e = new DLLElement(item,sortKey);

    if(IsEmpty())
    {
        first = e;
        if(errorNum==1)
        {
            //DEBUG('t',"Yield caused by error 1\n");
            printf("\n!!! Yield caused by error 1\n");
            currentThread->Yield();
        }
        last = e;
    }
    else if(sortKey < first->key)
    {
        e->next = first;
        first->prev = e;
       if(errorNum==2)
        {
            //DEBUG('t',"Yield caused by error 2\n");
            printf("\n!!! Yield caused by error 2\n");
            currentThread->Yield();
        }

        first = e;
    }
    else
    {
        DLLElement *tmp = first;

        //pointer postiton smallItem InsertItem tmp
        while(tmp != NULL)
        {
            if(tmp->key > sortKey)
                break;

            if(tmp->key <= sortKey)
                tmp = tmp->next;

        }

        //insterItem is new last
        if(tmp == NULL)
        {
            e->prev = last;
            last->next = e;
            if(errorNum==3)
            {
                //DEBUG('t',"Yield caused by error 3\n");
                printf("\n!!! Yield caused by error 3\n");
                currentThread->Yield();
            }
            last = e;
        }
        else
        {
            tmp->prev->next = e;
            e->prev = tmp->prev;
            tmp->prev = e;
            e->next = tmp;
        }

    }

    for(DLLElement *tmp = first;
            tmp != NULL;tmp = tmp->next)
    {
        printf("%d ",tmp->key);
    }
    printf("\n");
    lock->Release();
}

void *DLList::SortedRemove(int sortKey)
{
    lock->Acquire();
    DLLElement *e = first;
    void *itemPtr = NULL;
    while(e != NULL)
    {
        if(e->key >= sortKey)
            break;
        e = e->next;
    }

    if(e->key == sortKey)
        itemPtr = e->item;
    lock->Release();
    return itemPtr;
}
