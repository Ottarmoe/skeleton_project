#include "controller.h"
#include "driver/elevio.h"
#include <stdio.h>

#include "timer.h"
#include "doors.h"
#include "orderState.h"

bool homing = 0;
floor position = NO_FLOOR; //the floor at or below the elevator
bool stopped = 0;
bool onFloor = 0;
bool directionPreference;
MotorDirection motiondir = DIRN_STOP;
timespan stoppedUntil;

void CONTROL_HOME(floor f){
    homing = 1;
    ORDSTAT_DOINPUTS(0);
}

void CONTROL_RESET(){
    ORDSTAT_CLEAR();
    DOORS_CLOSE();
    elevio_stopLamp(0);
    position = NO_FLOOR;
    CONTROL_HOME(0);
}

void registerFloor(floor f){
    onFloor = 1;
    position = f;
    elevio_floorIndicator(f);
}
void setMotion(MotorDirection dirn){
    motiondir = dirn;
    elevio_motorDirection(dirn);
}


void CONTROL_UPDATE(){
    //stop button
    if(elevio_stopButton()){
        setMotion(DIRN_STOP);
        stopped = 1;
        stoppedUntil = getTime()+3000;
        elevio_stopLamp(1);
        ORDSTAT_CLEAR();
        ORDSTAT_DOINPUTS(0);

        floor sense = elevio_floorSensor();
        if(sense != -1){
            DOORS_CYCLE();
            registerFloor(sense);
        }
        return;
    }
    if(stopped){
        stopped = 0;
        elevio_stopLamp(0);
        ORDSTAT_DOINPUTS(1);
        return;
    }
    if(getTime() < stoppedUntil) return;


    floor sense = elevio_floorSensor();
    if(sense != -1) registerFloor(sense);
    else{
        if(onFloor && motiondir == DIRN_DOWN){
            position -= 1;
        }
        onFloor = 0;
    }

    //doors
    if(DOORS_AREOPEN()){
        if(sense != -1) ORDSTAT_CLOSE(sense);
        return;
    }

    //home
    if(homing){
        if(sense == -1){
            setMotion(DIRN_DOWN);
            return;
        }
        setMotion(DIRN_STOP);
        ORDSTAT_DOINPUTS(1);
        homing = 0;
    }

    //if at floor
    if(sense != -1){
        bool shouldCycle = ORDGET(sense, BUTTON_CAB);
        if(motiondir != DIRN_UP) 
            shouldCycle |= ORDGET(sense, BUTTON_HALL_DOWN);
        if(motiondir != DIRN_DOWN) 
            shouldCycle |= ORDGET(sense, BUTTON_HALL_UP);

        if(shouldCycle){
            setMotion(DIRN_STOP);
            DOORS_CYCLE();
            ORDSTAT_CLOSE(sense);
            return;
        }
    }

    //control algorithm

    /*floor target = ORDSTAT_OLDEST_CAB();
    if(target == NO_FLOOR) target = ORDSTAT_OLDEST_HALL();
    if(target == NO_FLOOR){
        setMotion(DIRN_STOP);
        return;
    }*/
    floor target = NO_FLOOR;
    if(directionPreference == 0){
        for(floor f = N_FLOORS-1; f>=0; --f){
            if(ORDGET(f, 0) || ORDGET(f, 1) || ORDGET(f, 2)){
                target = f;
            }
        }
    }
    else{
        for(floor f = 0; f<N_FLOORS; ++f){
            if(ORDGET(f, 0) || ORDGET(f, 1) || ORDGET(f, 2)){
                target = f;
            }
        }
    }
    if(target == NO_FLOOR){
        setMotion(DIRN_STOP);
        return;
    }

    if(target <= position){
        setMotion(DIRN_DOWN);
        directionPreference = 0;
        return;
    }
    if(target > position){
        setMotion(DIRN_UP);
        directionPreference = 1;
        return;
    }
}

void CONTROL_UPDATE_ARC(){
    //stop button
    if(elevio_stopButton()){
        setMotion(DIRN_STOP);
        stopped = 1;
        stoppedUntil = getTime()+3000;
        elevio_stopLamp(1);
        ORDSTAT_CLEAR();
        ORDSTAT_DOINPUTS(0);

        floor sense = elevio_floorSensor();
        if(sense != -1){
            DOORS_CYCLE();
            registerFloor(sense);
        }
        return;
    }
    if(stopped){
        stopped = 0;
        elevio_stopLamp(0);
        ORDSTAT_DOINPUTS(1);
        return;
    }
    if(getTime() < stoppedUntil) return;


    floor sense = elevio_floorSensor();
    if(sense != -1) registerFloor(sense);
    else{
        if(onFloor && motiondir == DIRN_DOWN){
            position -= 1;
        }
        onFloor = 0;
    }

    //doors
    if(DOORS_AREOPEN()){
        if(sense != -1) ORDSTAT_CLOSE(sense);
        return;
    }

    //home
    if(homing){
        if(sense == -1){
            setMotion(DIRN_DOWN);
            return;
        }
        setMotion(DIRN_STOP);
        ORDSTAT_DOINPUTS(1);
        homing = 0;
    }

    //if at floor
    if(sense != -1){
        bool shouldCycle = ORDGET(sense, BUTTON_CAB);
        if(motiondir != DIRN_UP) 
            shouldCycle |= ORDGET(sense, BUTTON_HALL_DOWN);
        if(motiondir != DIRN_DOWN) 
            shouldCycle |= ORDGET(sense, BUTTON_HALL_UP);

        if(shouldCycle){
            setMotion(DIRN_STOP);
            DOORS_CYCLE();
            ORDSTAT_CLOSE(sense);
            return;
        }
    }

    //control algorithm

    floor target = ORDSTAT_OLDEST_CAB();
    if(target == NO_FLOOR) target = ORDSTAT_OLDEST_HALL();
    if(target == NO_FLOOR){
        setMotion(DIRN_STOP);
        return;
    }
    
    if(target <= position){
        setMotion(DIRN_DOWN);
        return;
    }
    if(target > position){
        setMotion(DIRN_UP);
        return;
    }
}