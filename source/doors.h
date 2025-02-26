#ifndef DOORS
#define DOORS

#include <stdbool.h>

#define DOORS_obstructionDelay 3000;

void DOORS_OPEN();
void DOORS_CLOSE();
bool DOORS_AREOPEN();
void DOORS_UPDATE();

#define DOORS_cycleDelay 3000;
//opens and closes, must wait DOORS_cycleDelay before closing. May be overruled by DOORS_OPEN();
void DOORS_CYCLE();

#endif