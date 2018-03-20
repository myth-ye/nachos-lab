#include "copyright.h"
#include "utility.h"
#include "dllist.h"
#include "system.h"

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
}

DLList::~DLList()
{
    while(!IsEmpty())
        Remove(NULL);

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

}
void DLList::Append(void *item)
{
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

}

void *DLList::Remove(int *keyPtr)
{
    /* 垃圾英语不可原谅

    DLLElement *e = first;

    // find where key element is
    while(e != last)
    {
        if(e->key != *keyPtr)
            e = e->next;
    }

    //execute remove
    if(e == NULL)
        return NULL;
    else
    {
        e->prev->next = e->next;
        e->next->prev = e->prev;
        *keyPtr = e->key;
        void *thing = e->item;
        delete e;
        return item;
    }
    */

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

            //DEBUG
    printf("Remove head finish, DLList: ");
    for(DLLElement *tmp = first;
            tmp != NULL;tmp = tmp->next)
    {
        printf("%d ",tmp->key);
    }
    printf("\n");


    return itemPtr;
}

void DLList::SortedInsert(void *item, int sortKey)
{
    DLLElement *e = new DLLElement(item,sortKey);

    if(IsEmpty())
    {
        first = e;
        last = e;
    }
    else if(sortKey < first->key)
    {
        e->next = first;
        first->prev = e;
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
    //DEBUG
    printf("SortedInsert finish, DLList: ");
    for(DLLElement *tmp = first;
            tmp != NULL;tmp = tmp->next)
    {
        printf("%d ",tmp->key);
    }
    printf("\n");
}

void *DLList::SortedRemove(int sortKey)
{
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

    return itemPtr;
}
