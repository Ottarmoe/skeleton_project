#include <time.h>
#include <sys/time.h>
#include "timer.h"

timespan getTime(){
    struct timeval tp;

	gettimeofday(&tp, NULL);
	return tp.tv_sec * 1000 + tp.tv_usec / 1000;
}

//busy loop
void millisleep(timespan t){
    timespan endTime = getTime()+t;
    while(getTime() < endTime);
}