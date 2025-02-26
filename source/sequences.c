#include "sequences.h"
#include <stdio.h>
#include <string.h>

#include "driver/elevio.h"
#include "timer.h"
#include "doors.h"
#include "orderState.h"

void testClock(){
    printf("sleep\n");
    for(int i = 0; i<3; ++i){
        printf("tick\n");
        millisleep(1000);
    }
    printf("timer:\n");
    for(int i = 0; i<3; ++i){
        printf("tick\n");
        timespan currtime = getTime();
        while(getTime()<currtime+1000);
    }
}

void testDoors(){
    elevio_init();
    printf("press the elevator destination buttons to controll the doors\n"
        "1: open\n2: close\n3: cycle\nstop: quit\n");
    
    bool doorStateBuff = 0;
    while(1){
        if(elevio_stopButton()) return;
        if(elevio_callButton(0, 2)) DOORS_OPEN();
        if(elevio_callButton(1, 2)) DOORS_CLOSE();
        if(elevio_callButton(2, 2)) DOORS_CYCLE();
        
        DOORS_UPDATE();
        if(DOORS_AREOPEN() != doorStateBuff){
            doorStateBuff = DOORS_AREOPEN();
            printf("doors in state %i\n", doorStateBuff);
        }

        millisleep(20);
    }
}

void testOrderState(){
    elevio_init();
    ORDSTAT_DOINPUTS(1);
    printf("set obstruction to control, press stop to quit\n");
    printf("C: clear\nc: close\no: open\np: print\ni: oldest cab\ne: oldest hall\nq: set input\nh: help\n");
    
    while(1){
        if(elevio_stopButton()) return;
        if(elevio_obstruction()){
            char c;
            do{
                scanf("%c", &c);
            } while(strchr("Ccopieh", c)==NULL);
            
            if(c == 'C') ORDSTAT_CLEAR();
            else if(c == 'i') printf("Oldest cab order: %i\n", ORDSTAT_OLDEST_CAB());
            else if(c == 'e') printf("Oldest hall order: %i\n", ORDSTAT_OLDEST_HALL());
            else if(c == 'h') printf("C: clear\nc: close\no: open\np: print\ni: oldest cab\ne: oldest hall\nq: set input\nh: help\n");
            else if(c == 'p'){
                for(int f = N_FLOORS-1; f>=0; --f){
                    for(int b = 0; b<N_BUTTONS; ++b){
                        printf("%i %i, ", ORDGET(f, b), ORDINDEX(f, b));
                    }
                    printf("\n");
                }
            }
            else if(c == 'c'){
                floor f;
                scanf("%i", &f);
                ORDSTAT_CLOSE(f);
            }
            else if(c == 'o'){
                floor f;
                int b;
                scanf("%i %i", &f, &b);
                ORDSTAT_OPEN(f, b);
            }
            else if(c == 'q'){
                floor f;
                scanf("%i", &f);
                ORDSTAT_DOINPUTS(f);
            }
        }
        ORDSTAT_UPDATE();
        millisleep(20);
    }
}