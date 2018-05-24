#include"Alarm.h"
#include"system.h"
#include"utility.h"
Alarm::restNum = 0;
Alarm::Alarm()
{
    list = new List();
}

Alarm::~Alarm()
{
    delete list;
}

void change(int which)
{
    while(Alarm::restNum!=0)
        currentThread->Yield();
    printf("All threads done!\n");
}

void Alarm::Pause(int howLong)
{
    IntStatus oldLevel = interrupt->SetLevel(IntOff);   // disable interrupts
    restNum++;

    int wakeTime = stats->totalTicks + howLong*TimerTicks;
    list->SortedInsert(currentThread,wakeTime);

    if (restNum == 1)
    {
		Thread *t = new Thread("dummy thread");
		t->Fork(change,0);
	}

	currentThread->Sleep();

	(void) interrupt->SetLevel(oldLevel);   // re-enable interrupts
}

void Alarm::Wake()
{
    IntStatus oldLevel = interrupt->SetLevel(IntOff);   // disable interrupts


	int wakeTime;
	int num = restNum;
    Thread *nextThread;
	for(int i=0;i<num;i++)
    {
        nextThread = (Thread*)list->SortedRemove(&wakeTime);
        if(wakeTime < stats->totalTicks)
        {
            scheduler->ReadyToRun(nextThread);
            restNum--;
        }
        else
        {
            list->SortedInsert(nextThread,wakeTime);
            break;
        }

    }

    (void) interrupt->SetLevel(oldLevel);   // re-enable interrupts

}


