#include <time.h>
#include <stdio.h>
#include "timer.h"

timespan getTime(){
    return (clock()*1000)/CLOCKS_PER_SEC;
}

void testClock(){
    for(int i = 0; i<6; ++i){
        printf("tick\n");
        timespan currtime = getTime();
        while(getTime()<currtime+1000);
    }
}