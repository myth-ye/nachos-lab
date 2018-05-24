#include"EventBarrier.h"
#include"synch.h"

EventBarrier::EventBarrier()
{
    status = false;
    waitNum = 0;
    value = 0;
    barrierLock = new Lock("barrierlock");
    signal_con = new Condition("signalCondition");
    complete_con = new Condition("completeCondition");
}

EventBarrier::~EventBarrier()
{
    delete barrierLock;
    delete signal_con;
    delete complete_con;
}

void EventBarrier::Wait()
{
    barrierLock->Acquire();
    if(status==false)
    {
        waitNum++;
        signal_con->Wait(barrierLock);
        waitNum--;
    }
    barrierLock->Release();
}
void EventBarrier::Signal()
{
    barrierLock->Acquire();
    status = true;
    if(waitNum!=0)
    {
        signal_con->Broadcast(barrierLock);
        complete_con->Wait(barrierLock);
    }
    else
    {
        status = false;
    }

    barrierLock->Release();
}

void EventBarrier::Complete()
{
    barrierLock->Acquire();
    if(waitNum==0)
    {
        status = false;
        complete_con->Broadcast(barrierLock);
    }
    else
    {
        complete_con->Wait(barrierLock);
    }

    barrierLock->Release();
}

int EventBarrier::Waiters()
{
    barrierLock->Acquire();
    int ret = waitNum;
    barrierLock->Release();
    return ret;
}

