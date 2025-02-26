#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "driver/elevio.h"
#include "timer.h"
#include "sequences.h"

#include "doors.h"
#include "orderState.h"
#include "controller.h"


int main(){
    elevio_init();
    CONTROL_RESET(); 
    while(1){
        DOORS_UPDATE();
        ORDSTAT_UPDATE();
        CONTROL_UPDATE_ARC();
        if(elevio_stopButton() && elevio_obstruction()) break;

        millisleep(20);
    }
    return 0;
}