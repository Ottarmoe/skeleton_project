#include "timer.h"
#include "driver/elevio.h"
#include "doors.h"

timespan obstructedTime = 0;
typedef enum Goalstate {closed, open, cycle} Goalstate;

Goalstate goal;
Goalstate state;

void DOORS_OPEN(){
    goal = open;
}
void DOORS_CLOSE(){
    goal = closed;
}
void DOORS_CYCLE(){
    goal = cycle;
}


bool DOORS_AREOPEN(){
    return state == open;
}

void DOORS_UPDATE(){
    if(elevio_obstruction()) obstructedTime = getTime()+DOORS_obstructionDelay;
    if(state == goal) return;

    if(goal == open || goal == cycle){
        elevio_doorOpenLamp(1);
        state = open;
    }
    if(goal == cycle){
        goal = closed;
        obstructedTime = getTime()+DOORS_cycleDelay;
    }
    if(goal == closed){
        if(getTime() >= obstructedTime){
            elevio_doorOpenLamp(0);
            state = closed;
        }
    }
}