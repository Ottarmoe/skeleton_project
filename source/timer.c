#include <time.h>
#include <sys/time.h>
#include "timer.h"

timespan getTime(){
    //return (clock()*1000)/CLOCKS_PER_SEC;
    struct timeval tp;

	gettimeofday(&tp, NULL);
	return tp.tv_sec * 1000 + tp.tv_usec / 1000;
}

//hard to make work, please fix
void millisleep(timespan t){
    //nanosleep(&(struct timespec){0, t*1000*1000}, NULL);

    timespan endTime = getTime()+t;
    while(getTime() < endTime);
}