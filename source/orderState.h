#include <stdbool.h>
#include <limits.h>
#include "driver/elevio.h"

typedef int floor;

//no functions have security checks

//inputs not done by default
void ORDSTAT_DOINPUTS(bool set);

//checks for incoming orders depending on doinputs
void ORDSTAT_UPDATE();

//close all orders
void ORDSTAT_CLEAR();
//close all orders on a floor
void ORDSTAT_CLOSE(floor f);
void ORDSTAT_OPEN(floor f, ButtonType i);

bool ORDGET(floor f, ButtonType i);
//lower indexes for older orders
int ORDINDEX(floor f, ButtonType i);


#define NO_FLOOR INT_MIN

//returns NO_FLOOR if no applicable orders

int ORDSTAT_OLDEST_CAB();
int ORDSTAT_OLDEST_HALL();