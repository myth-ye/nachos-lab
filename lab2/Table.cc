#include"Table.h"
#include "synch.h"
#include "system.h"

Table::Table(char *debugname,int size)
{
    name = debugname;
    tsize = size;
    lock = new Lock(debugname);
    table = (void **)AllocBoundedArray(tsize*sizeof(void*));
    count = 0;
    for(int i=0;i<tsize;i++)
        table[i] = NULL;
}
Table::~Table()
{
    delete lock;
    DeallocBoundedArray((char *)table,tsize);
}
int Table::Alloc(void *object)
{
    lock->Acquire();
    int ret;
    if(count>=tsize)
        ret = -1;
    else
    {
        for(int i=0;i<tsize;i++)
            if(!table[i])
            {
                table[i] = object;
                ret = i;
                count++;
                break;
            }

    }

    lock->Release();
    return ret;
}
void* Table::Get(int index)
{
    ASSERT((index >= 0) && (index < tsize));
    lock->Acquire();
    void *ret = table[index];
    lock->Release();
    return ret;
}

void Table::Release(int index)
{
    lock->Acquire();
    table[index] = NULL;
    count--;
    lock->Release();
}
