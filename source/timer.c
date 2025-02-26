#include <time.h>
#include "timer.h"

timespan getTime(){
    return (clock()*1000)/CLOCKS_PER_SEC;
}

//hard to make work, please fix
void millisleep(timespan t){
    //nanosleep(&(struct timespec){0, t*1000*1000}, NULL);

    timespan endTime = getTime()+t;
    while(getTime() < endTime);
}