#ifndef ALARM_H
#define ALARM_H

#include "list.h"

class Alarm{
    public:
        Alarm();
        ~Alarm();
        void Pause(int howLong);
        void Wake();
        static int restNum;
    private:
        List *list;
};

#endif // ALARM_H
