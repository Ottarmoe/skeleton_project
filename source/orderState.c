#include "orderState.h"

bool doInputs = 0;
int nextindex = 0;
int ordIndecies[N_FLOORS*N_BUTTONS];
bool ordStatus[N_FLOORS*N_BUTTONS];

void ORDSTAT_DOINPUTS(bool set){
    doInputs = set;
}

bool ORDGET(int f, ButtonType i){
    return ordStatus[N_BUTTONS*f+i];
}
int ORDINDEX(int f, ButtonType i){
    return ordIndecies[N_BUTTONS*f+i];
}

void ORDSTAT_CLOSE(int f){
    for(int b = 0; b < N_BUTTONS; ++b){
        ordStatus[f*N_BUTTONS+b] = 0;
        elevio_buttonLamp(f, b, 0);
    }
}
void ORDSTAT_CLEAR(){
    for(int f = 0; f < N_FLOORS; ++f)
        ORDSTAT_CLOSE(f);
    nextindex = 0;
}
void ORDSTAT_OPEN(int f, ButtonType i){
    if(ORDGET(f, i)) return;
    ordStatus[N_BUTTONS*f+i] = 1;
    ordIndecies[N_BUTTONS*f+i] = nextindex++;
    elevio_buttonLamp(f, i, 1);
}

void ORDSTAT_UPDATE(){
    if(doInputs)
        for(int f = 0; f<N_FLOORS; ++f)
            for(int b = 0; b<N_BUTTONS; ++b)
                if(elevio_callButton(f, b)) ORDSTAT_OPEN(f, b);
}

int ORDSTAT_OLDEST_CAB(){
    int oldest = NO_FLOOR;
    int ind = INT_MAX;
    for(int f = 0; f<N_FLOORS; ++f)
        if(ORDGET(f, BUTTON_CAB))
        if(ORDINDEX(f, BUTTON_CAB) < ind){
            oldest = f;
            ind = ORDINDEX(f, BUTTON_CAB);
        }
    return oldest;
}
int ORDSTAT_OLDEST_HALL(){
    int oldest = NO_FLOOR;
    int ind = INT_MAX;
    for(int f = 0; f<N_FLOORS; ++f){
        if(ORDGET(f, BUTTON_HALL_UP))
        if(ORDINDEX(f, BUTTON_HALL_UP) < ind){
            oldest = f;
            ind = ORDINDEX(f, BUTTON_HALL_UP);
        }

        if(ORDGET(f, BUTTON_HALL_DOWN))
        if(ORDINDEX(f, BUTTON_HALL_DOWN) < ind){
            oldest = f;
            ind = ORDINDEX(f, BUTTON_HALL_DOWN);
        }
    }
    return oldest;
}