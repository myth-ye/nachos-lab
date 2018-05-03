#include "BoundedBuffer.h"
#include "synch.h"
#include "system.h"

BoundedBuffer::BoundedBuffer(int maxsize)
{
    lock = new Lock("BoundedBuffer lock");
    bufferFull = new Condition("bufferFull");
    bufferEmpty = new Condition("bufferEmpty");
    bsize = maxsize;
    count = 0;
    nextRead = 0;
    nextWrite = 0;
    buffer = (int *)AllocBoundedArray(bsize*sizeof(int));
}
BoundedBuffer::~BoundedBuffer()
{
    DeallocBoundedArray((char *)buffer,bsize);
    delete lock;
    delete bufferEmpty;
    delete bufferFull;
}
void BoundedBuffer::Read(void *data, int size)
{
    int *rdata =(int *)data;
    while(size!=0)
    {
        lock->Acquire();

        while(count==0) bufferEmpty->Wait(lock);

        *rdata = buffer[nextRead];
        rdata++;
        nextRead = (nextRead + 1) % bsize;
        count--;
        bufferFull->Broadcast(lock);
        size--;

        lock->Release();
    }
}

void BoundedBuffer::Write(void *data,int size)
{
    int *wdata = (int *)data;
    while(size!=0)
    {
        lock->Acquire();
        while(count==bsize)bufferFull->Wait(lock);
        buffer[nextWrite] = *wdata;
        wdata++;
        nextWrite = (nextWrite + 1 ) % bsize;
        count++;
        size--;
        bufferEmpty->Broadcast(lock);

        lock->Release();
    }
}
