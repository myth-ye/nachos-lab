// threadtest.cc
//	Simple test case for the threads assignment.
//
//	Create two threads, and have them context switch
//	back and forth between themselves by calling Thread::Yield,
//	to illustratethe inner workings of the thread system.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "dllist.h"
#include "time.h"
#include "string.h"
#include "BoundedBuffer.h"
#include "Table.h"
// testnum is set in main.cc
int testMode = 1;
int threadNum = 1;
int itemNum = 10;
int errorNum = -1;
int data[20]={0};

DLList *l = new DLList;
Table *table = new Table("tableTest",10);
BoundedBuffer* buffer = new BoundedBuffer(50);


void
DDlistTestFunc(int randkey)
{
    printf("thread %d starts \n",randkey);
    //threadname has bug in DEBUG()  use randkey to identify thread
    RandomInit((unsigned)time(NULL)+randkey);
    addNRandom(itemNum,l);
    removeNitem(itemNum,l);
}

void
DDlistTest()
{
    printf("Entering DDlist ThreadTest\n");
    for(int i=0;i<threadNum;i++)
    {
        char name[10] = "Thread0";
        name[6] = '0'+i;
        Thread *t = new Thread(name);

        t->Fork(DDlistTestFunc,i);//i for random seed
    }


}

void BoundedBufferFunc(int which)
{

    if (which == 0)
    {
        printf("produce starts in thread %d\n", which);
        buffer->Write((void *)data, 20);
    } else
    {
        printf("comsume starts in thread %d\n", which);

        int* consumedata = new int[which];
        buffer->Read((void *)consumedata, which);

        printf("comsume thread %d read data:",which);
        for(int i = 0; i < which; i++)
            printf("%d ",consumedata[i]);

        printf("\nconsumer completed in thread %d\n", which);
    }
}

void BoundedBufferTest()
{
    RandomInit((unsigned)time(NULL));
    printf("the data is:");
    for(int i=0;i<20;i++)
        printf("%d ",data[i]=Random()%100);
    printf("\n");

    for(int i=0;i<threadNum;i++)
    {
        char name[10] = "Thread0";
        name[6] = '0'+i;
        Thread *t = new Thread(name);

        t->Fork(BoundedBufferFunc,i);//i for thread number
    }
}

void TestTableFunc(int which)
{
    RandomInit((unsigned)time(NULL)+which);
    int *object = new int;
    *object = Random()%100;

    int index = table->Alloc((void *)object);
    printf("thread %d:add object %d to table\n", which, *object);


    currentThread->Yield();

    if (index != -1) {
        ASSERT(((int *)table->Get(index))==object);
        printf("thread %d:get object %d and release from table\n", which, *(int *)(table->Get(index)));
        table->Release(index);
    }

    currentThread->Yield();
}

void TestTable()
{

    for(int i=0;i<threadNum;i++)
    {
 //       char name[10] = "Thread0";
 //       name[6] = '0'+i;
        char *name;
        if(i==0)
            name = "Thread0";
        else
            name = "Thread1";
        Thread *t = new Thread(name);
        t->Fork(TestTableFunc,i);//i for random seed and thread number
    }
}


void ThreadTest()
{

    switch (testMode) {
    case 1:
        DDlistTest();
        break;
	case 2:
        BoundedBufferTest();
        break;
    case 3:
        TestTable();
        break;
    default:
	printf("No test specified.\n");
	break;
    }
}


