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
// testnum is set in main.cc
int threadNum = 1;
int itemNum = 10;
int errorNum = 1;

DLList *l = new DLList;
//----------------------------------------------------------------------
// SimpleThread
// 	Loop 5 times, yielding the CPU to another ready thread
//	each iteration.
//
//	"which" is simply a number identifying the thread, for debugging
//	purposes.
//----------------------------------------------------------------------

void
SimpleThread(int randkey)
{
/*    int num;

    for (num = 0; num < 5; num++) {
	printf("*** thread %d looped %d times\n", which, num);
        currentThread->Yield();
    }*/
    RandomInit((unsigned)time(NULL)+randkey);

    addNRandom(itemNum,l);
    removeNitem(itemNum,l);
}

//----------------------------------------------------------------------
// ThreadTest1
// 	Set up a ping-pong between two threads, by forking a thread
//	to call SimpleThread, and then calling SimpleThread ourselves.
//----------------------------------------------------------------------

void
DDlistTest()
{
    DEBUG('t', "Entering DDlist ThreadTest\n");
    for(int i=0;i<threadNum;i++)
    {
   // there is an unfixed bug
   //     char name[20];
   //     char greeting[6] = {'H', 'e', 'l', 'l', 'o', '\0'};

   //     sprintf(name,"%s,%d","thread",i);
  //      threadname[3]='a'+i;
      //  threadname[strlen(threadname)]='\0';
     //   char *testc = "N-thread";
        //*(testc+1)='a'+i;
        Thread *t = new Thread("cantChangeThreadName");

        t->Fork(SimpleThread,i);
    }

   // SimpleThread(0);
}

//----------------------------------------------------------------------
// ThreadTest
// 	Invoke a test routine.
//----------------------------------------------------------------------

/*void
ThreadTest()
{
    switch (testnum) {
    case 1:
	ThreadTest1();
	break;
    default:
	printf("No test specified.\n");
	break;
    }
}
*/
